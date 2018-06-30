import javax.swing.*;
import javax.swing.text.*;
import java.awt.event.*;
import java.awt.*;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.text.ParseException;
import java.util.Calendar;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.zip.DataFormatException;
import com.sun.org.apache.xalan.internal.xsltc.compiler.util.StringStack;
import javax.swing.text.rtf.RTFEditorKit;
import java.io.*;

public abstract class BasedMemo {
    abstract String getText();
    static void insert(DefaultStyledDocument doc,StyleContext sc,String text){
        StringBuffer sb = new StringBuffer();
        sb.append(text);

        try{
            doc.insertString(doc.getLength(), new String(sb),
                    sc.getStyle(StyleContext.DEFAULT_STYLE));
        }catch (BadLocationException ble){
            System.err.println("エラーが発生しました");
        }
        return;
    }
}
class Memo extends  BasedMemo{
    @Override
    String getText() {
        Calendar cl = Calendar.getInstance();
            SimpleDateFormat date = new SimpleDateFormat("yyyy/MM/dd");
            return date.format(cl.getTime()).toString() + "\n";
    }
}

class ToDo extends BasedMemo{
    String to_do = "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "□　　　　　　　　　　　　　　　　　　　                                                     \n" +
            "　　　　　　　　　　　　　　　　　　　　";
    @Override
    String getText(){
        return to_do;
    }
}

class AuthorName extends BasedMemo{
    String getText(){
        try {
            return "Author : "+InetAddress.getLocalHost().getHostName() + "\n";
        } catch (UnknownHostException e1) {
            e1.printStackTrace();
            return "Author Unknown" + "\n";

        }
    }
}


