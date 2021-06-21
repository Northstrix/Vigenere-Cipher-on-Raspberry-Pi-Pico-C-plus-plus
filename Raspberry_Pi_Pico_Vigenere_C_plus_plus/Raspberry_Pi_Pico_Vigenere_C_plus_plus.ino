// Vigenere cipher on Raspberry Pi Pico C++
// Ported by Maxim Bortnikov
// For more information please visit: https://github.com/Northstrix/Vigenere-Cipher-on-Raspberry-Pi-Pico-C-plus-plus
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Function to convert the "ASCII mess" to the readable string
void asciiToSentence(String str, int len, int row)
{
    int num = 0;
    for (int i = 0, p = 0; i < len; i++) {
 
        // Append the current digit
        num = num * 10 + (str[i] - '0');
 
        // If num is within the required range
        if (num >= 32 && num <= 122) {
 
            // Convert num to char
            char ch = (char)num;
            Serial.print(ch);
            lcd.setCursor(p,row); 
            // Print the data on display
            lcd.print(ch);
            p++;
 
            // Reset num to 0
            num = 0;
        }
    }
  Serial.println("");
}
 
// Encryption Function
String get_encryption(String pt, String k){
 
    String ct = "";
    for(int i=0;i<pt.length();i++)
        ct += (char) (((int)pt[i]-'A' + (int)k[i]-'A') % 26) + 'A';
 
    return ct;
}
 
// Decryption Function
String get_decryption(String ct, String k){
 
    String pt = "";
    for(int i=0;i<ct.length();i++)
        pt += (char) ((((int)ct[i]- 'A' - (k[i] -'A')) + 26) % 26) + 'A';
 
    return pt;
}

void setup() {
  Serial.begin(115200);
  lcd.begin(24,2);  /* Initialize 16x2 LCD */
  lcd.clear();  /* Clear the LCD */
}

void loop() {
    int x;
     while (x) {
        Serial.println("");
        Serial.println("What are you going to do?");
        Serial.println("1.Encrypt");
        Serial.println("2.Decrypt");
        while (!Serial.available()) {}
        x = Serial.parseInt();
       if (x == 1) {
       lcd.clear();
       String plaintext;
       String key;
       Serial.println("Enter the plaintext");
       while (!Serial.available()) {}
       plaintext = Serial.readString();
       Serial.println("Enter the key");
       while (!Serial.available()) {}
       key = Serial.readString();
       Serial.print("Ciphertext:");
       // Function call to encode the data
       String ciphertext = get_encryption(plaintext, key);
       // Print plaintext on display
       lcd.setCursor(0,0);
       lcd.print(plaintext);
       int clen = ciphertext.length();
       asciiToSentence(ciphertext, clen, 1);
       delay(1000);
       }
       
       if (x == 2) {
       lcd.clear();
       String ciphertext;
       String key;
       Serial.println("Enter the ciphertext");
       while (!Serial.available()) {}
       ciphertext = Serial.readString();
       Serial.println("Enter the key");
       while (!Serial.available()) {}
       key = Serial.readString();
       Serial.print("Plaintext:");
       // Function call to decode the data
       String plaintext = get_decryption(ciphertext, key);
       // Print plaintext on display
       lcd.setCursor(0,0);
       lcd.print(ciphertext);
       int plen = plaintext.length();
       asciiToSentence(plaintext, plen, 1);
       delay(1000);
       }     
    }
}
