package ws;
 
import java.awt.Image;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

import javax.xml.ws.soap.MTOM; 


@MTOM(enabled=true)
@WebService
@SOAPBinding(style = Style.RPC)
public interface ImageServer{
 
	//download a image from server
	@WebMethod Image downloadImage(String name);
 
	
}
