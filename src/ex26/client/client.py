from suds.client import Client

url = "http://localhost:9999/ws/hello?wsdl"

client = Client(url)

response = client.service.getHelloWorldAsString("Plop")

print response
