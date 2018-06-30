import java.io.File;
import javax.swing.*;
import javax.swing.filechooser.*;

public class IsRtf extends  FileFilter{
    public boolean accept (File f){
        if(f.isDirectory())
            return true;
        String  s = "";
        String  t = f.getName();
        System.out.println(t);
        t = t.toLowerCase();
        for(int i = t.length() - 1; i >= 0;--i){
            if(t.charAt(i) == '.')break;
            s += t.charAt(i);
        }
        System.out.println(s);
        return (s.equals("ftr"));
    }
    @Override
    public String getDescription() {
        return "RTFOnly";
    }
}
