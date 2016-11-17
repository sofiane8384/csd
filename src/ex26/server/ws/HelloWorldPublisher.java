package ws;

import javax.xml.ws.Endpoint;
import ws.HelloWorldImpl;

//Endpoint publisher
public class HelloWorldPublisher{

	public static void main(String[] args) {
	    String url = "http://localhost:9999/ws/hello";
            Endpoint.publish(url, new HelloWorldImpl());
            System.out.println("WS deployed. WSDL URL: "+url+"?wsdl");

    }

}
