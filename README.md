# prokey_rfid
This is a library to combine the inputs on the ProKey WIEGAND receiver and combine them into a single output

It brings in the FOUR Wiegand inputs from the ProKet WIEGAND receiver, purcahsed from CSD in Australia, and retransmits the ID, setting the higher order bits depending on what button is pressed.

Use Case
The Use Case for this device is having a cheap FOB for the InnerRange Inception or Integriti. In the case of the Inception, I have created a user for the Wiegand code outputted from each button press, and then perform custom actions based on that user. I may add examples later. For now, these might be described as 'Arm', 'Disarm', 'Unlock Door'. etc. 
