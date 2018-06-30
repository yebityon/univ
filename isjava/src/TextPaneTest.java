import com.sun.org.apache.xalan.internal.xsltc.compiler.util.StringStack;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.event.*;
import java.awt.event.*;
import java.awt.*;
import javax.swing.text.rtf.RTFEditorKit;
import java.io.*;



public class TextPaneTest extends JFrame implements ActionListener{

    protected JTextPane textPane;

    protected DefaultStyledDocument doc;
    protected StyleContext sc;

    protected JToolBar toolBar;

    protected JComboBox comboFonts;
    protected JComboBox comboSizes;
    protected JComboBox comboType;
    protected RTFEditorKit rtfEditor;
    public static void main(String[] args){
        TextPaneTest test = new TextPaneTest();

        test.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        test.setVisible(true);
    }

    TextPaneTest(){
        String Titlename = "Practice";
        rtfEditor = new RTFEditorKit();
        setTitle(Titlename);
        setBounds( 10, 10, 800, 800);
        initToolbar();
        JMenuBar fileMenu = initFIleMenuBar();
        getContentPane().add(toolBar, BorderLayout.NORTH);

        textPane = new JTextPane();
        JScrollPane scroll = new JScrollPane(textPane,
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
                JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

        getContentPane().add(scroll, BorderLayout.CENTER);
        int condition = JComponent.WHEN_FOCUSED;
        InputMap iMap = textPane.getInputMap(condition);
        ActionMap aMap = textPane.getActionMap();
        iMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0), "enter");
        aMap.put("enter", new AbstractAction() {
            @Override
            /*
                  when enter key  pressed
             */
            public void actionPerformed(ActionEvent arg0){
                ReplaceText(textPane, "Windows", "Machintosh");
                ReplaceText(textPane,"Emacs","Vim");
                };
            }
        );

        sc = new StyleContext();
        doc = new DefaultStyledDocument(sc);
        textPane.setDocument(doc);
        setJMenuBar(fileMenu);

    }
    protected void initToolbar(){
        toolBar = new JToolBar();
        toolBar.setLayout(new FlowLayout(FlowLayout.LEFT));

        GraphicsEnvironment ge =
                GraphicsEnvironment.getLocalGraphicsEnvironment();
        String familyName[] = ge.getAvailableFontFamilyNames();

        //setting JcomboBox family name
        comboFonts = new JComboBox(familyName);
        comboFonts.setMaximumSize(comboFonts.getPreferredSize());
        comboFonts.addActionListener(this);
        comboFonts.setActionCommand("comboFonts");
        toolBar.add(comboFonts);
        toolBar.addSeparator();
        comboSizes = new JComboBox(new String[] {"8", "9", "10",
                "11", "12", "14", "16", "18", "20", "22", "24", "26",
                "28", "36", "48", "72"});
        comboSizes.setMaximumSize(comboSizes.getPreferredSize());
        comboSizes.addActionListener(this);
        comboSizes.setActionCommand("comboSizes");
        toolBar.add(comboSizes);

        comboType = new JComboBox(new String[]{
                "Date", "To Do" ,"Author"
        });
        comboType.addActionListener(this);
        comboType.setActionCommand("comboType");
        toolBar.add(comboType);
    }

    protected JMenuBar initFIleMenuBar(){
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File",true);
        menuBar.add(fileMenu);
        JMenuItem openItem  = new JMenuItem("Open");
        fileMenu.add(openItem);
        openItem.addActionListener(this);
        openItem.setActionCommand("openItem");
        JMenuItem saveItem = new JMenuItem("Save");
        fileMenu.add(saveItem);
        saveItem.addActionListener(this);
        saveItem.setActionCommand("saveItem");
        JMenuItem  clearItem = new JMenuItem("Clear");
        fileMenu.add(clearItem);
        clearItem.addActionListener(this);
        clearItem.setActionCommand("Clear");
        JMenuItem copyItem = new JMenuItem("Copy");
        fileMenu.add(copyItem);
        copyItem.addActionListener(this);
        copyItem.setActionCommand("Copy");
        fileMenu.addSeparator();

        return menuBar;

    }

    /*
        Action handller
     */
    public void actionPerformed(ActionEvent e){
        String actionCommand = e.getActionCommand();
        MutableAttributeSet attr = new SimpleAttributeSet();

        JFileChooser chooser = new JFileChooser();
        IsRtf filter = new IsRtf();
        chooser.setFileFilter(filter);
        if (actionCommand.equals("comboFonts")){
            String fontName = comboFonts.getSelectedItem().toString();
            StyleConstants.setFontFamily(attr, fontName);

        }else if (actionCommand.equals("comboSizes")){
            int fontSize = 0;

            try{
                fontSize = Integer.parseInt(comboSizes.
                        getSelectedItem().toString());

            }catch (NumberFormatException ex){
                System.out.println("NumberFormatException ex");
            }

            StyleConstants.setFontSize(attr, fontSize);

        } else if(actionCommand.equals("comboType")){
            String TypeOfMemo = comboType.getSelectedItem().toString();
            if(TypeOfMemo.equals("Date"))
            {
                Memo M = new Memo();
                Memo.insert(doc,sc,M.getText());
            }
            else if(TypeOfMemo.equals("To Do")){
                ToDo td = new ToDo();
                Memo.insert(doc,sc,td.getText());
            } else if(TypeOfMemo.equals("Author")){
                AuthorName o = new AuthorName();
                Memo.insert(doc,sc,o.getText());
            }

        /*
            Action handler which relate with filem menu
         */
        } else if(actionCommand.equals("saveItem")) {
            if (chooser.showSaveDialog(this) != JFileChooser.APPROVE_OPTION)
                return;
            File filechose = chooser.getSelectedFile();
            try {
                OutputStream out = new FileOutputStream(filechose);
                rtfEditor.write(out, doc, 0, doc.getLength());
                out.close();
            } catch (Exception ex) {
                ex.printStackTrace();

            }
            setTitle(filechose.getName());

        } else if(actionCommand.equals("openItem")){
            if(chooser.showOpenDialog(this) != JFileChooser.APPROVE_OPTION)
                return;
            File filechoose = chooser.getSelectedFile();
            doc = new DefaultStyledDocument(sc);
            try{
                InputStream input = new FileInputStream(filechoose);
                rtfEditor.read(input,doc,0);
                input.close();

            }catch (Exception ex){
                return;
            }
            textPane.setDocument(doc);
            setTitle(filechoose.getName());


        } else if(actionCommand.equals("Clear")) {
            textPane.setText(null);
        }else if(actionCommand.equals("Copy")){
            textPane.selectAll();
            textPane.copy();

        }
        setAttributeSet(attr);
        textPane.requestFocusInWindow();
    }



    /*
        Setting the AttributeSet here

     */
    void setAttributeSet(AttributeSet attr) {
        int start = textPane.getSelectionStart();
        int end = textPane.getSelectionEnd();
        int legnth  =  end - start;
        /*
            if legnth is zero, we change the textpane's attributes
         */
        if(legnth == 0)
        {
            textPane.setCharacterAttributes(attr,true);
        }
        else
            doc.setCharacterAttributes(start, legnth, attr, false);
    }


    /*
        ReplaceText
     */
    void ReplaceText(JTextPane textpane, String s, String u) {
        String text = textPane.getText();
        for (int i = 0; i < text.length() - s.length() + 1; i++) {
            String temp = text.substring(i, i + s.length());
            //System.out.println(temp);
            if (temp.equals(s)) {
                MutableAttributeSet attr = new SimpleAttributeSet();
                try {
                    doc.replace(i, s.length(), u, attr);

                } catch (BadLocationException e) {
                    System.err.println("hoge");
                }
            }
        }
    }
}

