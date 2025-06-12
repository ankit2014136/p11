package com.barco.clickshare.productionapi;

import java.io.IOException;
import java.net.URISyntaxException;
import java.security.GeneralSecurityException;

import com.microsoft.azure.sdk.iot.device.DeviceClient;
import com.microsoft.azure.sdk.iot.device.IotHubClientProtocol;
import com.microsoft.azure.sdk.iot.device.Message;
import com.microsoft.azure.sdk.iot.device.exceptions.IotHubClientException;

/** Sends a number of event messages to an IoT Hub. */
public class IoTHubClient
{
    //PEM encoded representation of the public key certificate

    // The maximum amount of time to wait for a message to be sent. Typically, this operation finishes in under a second.
    private static final int D2C_MESSAGE_TIMEOUT_MILLISECONDS = 10000;

    /**
     * Sends a number of messages to an IoT Hub. Default protocol is to 
     * use MQTT transport.
     *
     * @param args
     * args[0] = IoT Hub connection string
     * args[1] = number of requests to send
     * args[2] = IoT Hub protocol to use, optional and defaults to MQTT
     */
    public static void main(String[] args) throws IOException, URISyntaxException, GeneralSecurityException, IotHubClientException, InterruptedException
    {
        System.out.println("Starting...");

        String connectionString = "Hostname=iot-platform-develop-iothub.azure-devices.net;DeviceId=test-sant;x509=true";
        String hostName = "iot-platform-develop-iothub.azure-devices.net";
        String deviceId = "test-san1";
        //String publicKeyCertificateString = new String(Files.readAllBytes(Paths.get("/tmp/device_cer.pem")),StandardCharsets.UTF_8);
       // String privateKeyString = new String(Files.readAllBytes(Paths.get("/tmp/device_key.pem")),StandardCharsets.UTF_8);

        int numRequests = 5;
        IotHubClientProtocol protocol = IotHubClientProtocol.HTTPS;
        System.out.format("Using communication protocol %s.\n", protocol.name());

        PKCS11SecurityProvider provider = new PKCS11SecurityProvider();

        //SSLContext sslContext = SSLContextBuilder.buildSSLContext(publicKeyCertificateString, privateKeyString);
        //ClientOptions clientOptions = ClientOptions.builder().sslContext(ctx).build();
        
        DeviceClient client = new DeviceClient(hostName, deviceId, provider,  IotHubClientProtocol.HTTPS);
        //DeviceClient client = new DeviceClient(connectionString, protocol, clientOptions);

        System.out.println("Successfully created an IoT Hub client.");

        client.open(true);

        System.out.println("Opened connection to IoT Hub.");
        System.out.println("Sending the following event messages:");

        for (int i = 0; i < numRequests; ++i)
        {
            double temperature = 20 + Math.random() * 10;
            double humidity = 30 + Math.random() * 20;

            String msgStr = "{\"temperature\":"+ temperature +",\"humidity\":"+ humidity +"}";
            
            try
            {
                Message msg = new Message(msgStr);
                msg.setContentType("application/json");
                msg.setProperty("temperatureAlert", temperature > 28 ? "true" : "false");
                msg.setMessageId(java.util.UUID.randomUUID().toString());
                System.out.println(msgStr);

                client.sendEvent(msg, D2C_MESSAGE_TIMEOUT_MILLISECONDS);
                System.out.println("Successfully sent the message");
            }
            catch (IotHubClientException e)
            {
                //Exception ex = new Exception();
                //ex.getMessage()
                System.out.println("Failed to send the message. Status code: " + e.getStatusCode() + e.getMessage());
            }
        }
        
        // close the connection
        System.out.println("Closing the client...");
        client.close();
    }
}