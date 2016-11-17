
from suds.client import Client

url= "http://www.webservicex.com/globalweather.asmx?wsdl"
 
client = Client(url)

#pour voir l'objet client          

print client 
              
clientclient.service.GetCitiesByCountry("France")
                
clientclient.service.GetWeather ("France","Besancon")
