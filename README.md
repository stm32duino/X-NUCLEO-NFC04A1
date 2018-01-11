# X-NUCLEO-NFC04A1

Arduino library to support the X-NUCLEO-NFC04A1 expansion board. The X-NUCLEO-NFC04A1 dynamic NFC/RFID tag IC expansion board is based on 
the ST25DV04K NFC Type V/RFID tag IC with a dual interface 4 Kbits EEPROM that also features an I²C interface. It can be powered by the pin 
of Arduino connector or directly by the received carrier electromagnetic field.

## Examples

There are 2 examples with the X-NUCLEO-NFC04A1 library:
* X_NUCLEO_NFC04A1_HelloWorld: This application writes a URI tag on the device. It records an URI.

When the NFC module is started and ready, the message "Sytstem init done!" is displayed on the monitor window.
Next, the tag is written, we wait few seconds, we read the same tag and print it on the monitor window.

You can test this application by connecting it with your smartphone.
On Android, donwload a NFC Tools. Then start the app, check if NFC is activated
on your smartphone. Put your smartphone near the tag, you can read it. You can
write a tag with this app.

* X_NUCLEO_NFC04A1_SimpleWrite: This application writes a NDEF message, containg a URI record, to the tag.

When the NFC module is started and ready, the message "System init done!" is displayed on the monitor window.
Next, the tag is written with a URI.

You can test this application by tapping the tag with your smartphone.
On Android, check if NFC is activated on your smartphone.
Put your smartphone near the tag to read it.
The prefered Internet Browser is automatically opened with the provided URI.

## Documentation

You can find the source files at  
https://github.com/stm32duino/X-NUCLEO-NFC04A1

The ST25DV04K datasheet is available at  
http://www.st.com/content/st_com/en/products/nfc/st25-nfc-rfid-tags-readers/st25-dynamic-nfc-tags/st25dv-series-dynamic-nfc-tags/st25dv04k.html
