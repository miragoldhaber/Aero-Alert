// add to the sky spy 2
#ifndef ADAFRUIT_IO_HPP
#define ADAFRUIT_IO_HPP
//get my key
#define IO_USERNAME "mira_g"
#define IO_KEY "aio_Wbaf05ckxTjPqCBfWpvnaueSNvCt"
//add whichever wifi I use + password
// figure out how it can work in diff places
#define WIFI_SSID "Fios-Q3R6Q"
#define WIFI_PASS "ron8044fund856aim"

#include <AdafruitIO_WiFi.h>
#include <tempsensor.hpp>
#include <GPS.hpp>

namespace adafruit_io{
    float last_latitude{};
    float last_longitude{};
    float last_altitude{};
    float last_temp{};
    float last_gas{};
    float last_humid{};

    bool IO_connected {false};

    // IO Handler
    AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

    // Feeds
    AdafruitIO_Feed *gpscoords = io.feed("GPS Coordinates");
    AdafruitIO_Feed *humidity = io.feed("Humidity");
    AdafruitIO_Feed *temp = io.feed("Temperature");
    AdafruitIO_Feed *gas = io.feed("Gas In Kohms");

    void attempt_connection(){
        Serial.print("Connecting to Adafruit IO");

        io.connect();

        //waits for a connection for 30 seconds
        for (std::size_t i{0}; (i < 60) && (io.status() < AIO_CONNECTED); i++) {
            Serial.print(io.statusText());
            delay(500);
        }

        if (io.status() < AIO_CONNECTED){
            Serial.println("Connection failed");
            temperature::display();
        } else {
            Serial.println("Connected to Adafruit IO \n");
            Serial.println(io.statusText());
            IO_connected = true;
        }

    }
}



#endif //ADAFRUIT_IO_HPP