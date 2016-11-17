package ws;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class Message {

    private String msg;
    private int id;

    public void setId(int id)
    {
        this.id=id;
    }
    public void setMsg(String msg)
    {
        this.msg=msg;
    }

    public int getId()
    {
        return this.id;
    }
    public String getMsg()
    {
       return  this.msg;
    }

}
