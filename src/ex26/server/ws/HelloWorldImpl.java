package ws;

import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;
//Service Implementation
@WebService(endpointInterface = "ws.HelloWorld")
@SOAPBinding(style = Style.RPC) //optional
public class HelloWorldImpl implements HelloWorld{

	@Override
	public Message getHelloWorldAsString(String name) {
 
              Message msg = new Message();
              msg.setId(100);
              msg.setMsg("Hello World JAX-WS " + name);        
              return msg;
	}
}
