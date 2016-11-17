package ws;

import java.awt.Image;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.jws.WebService;
import javax.xml.ws.WebServiceException;
import javax.xml.ws.soap.MTOM; 


@MTOM(enabled=true)
@WebService(endpointInterface = "ws.ImageServer")

public class ImageServerImpl implements ImageServer{
 
	private static final String IMAGES_FOLDER = "/tmp/";

	@Override
	public Image downloadImage(String name) {
 
		try {
 
		File image = new File(IMAGES_FOLDER + name);
			return ImageIO.read(image);
 
                } catch (IOException e) {

                    e.printStackTrace();
                    return null; 

                }
        }

}
