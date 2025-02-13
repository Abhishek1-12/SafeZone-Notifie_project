import serial
import time
import pyautogui
import pyperclip  # For handling emojis
import os
from datetime import datetime

# Arduino Serial Configuration
arduino_port = "COM6"  # Replace with your Arduino's COM port
baud_rate = 9600
threshold_distance = 40  # Distance in cm to trigger action

# Initialize serial communication with Arduino
arduino = serial.Serial(arduino_port, baud_rate)
time.sleep(2)  # Wait for the connection to initialize

# WhatsApp App Path (update this path as per your system)
whatsapp_app_path = r"C:\Users\Lenovo\OneDrive\Desktop\WhatsApp.lnk"

# Recipient phone number
recipient_phone_number = "9910930858"

# Function to close the currently active app
def close_current_app():
    pyautogui.hotkey("alt", "f4")
    print("Closed the currently active app.")

# Function to send a WhatsApp message
def send_whatsapp_message():
    # Open WhatsApp app
    os.startfile(whatsapp_app_path)
    time.sleep(5)  # Wait for WhatsApp to open completely

    # Open the search box (Ctrl + F)
    pyautogui.hotkey("ctrl", "f")
    time.sleep(1)

    # Type recipient's phone number
    pyautogui.typewrite(recipient_phone_number)
    time.sleep(2)

    # Press Enter to select the chat
    pyautogui.press("enter")
    time.sleep(3)  # Wait for the chat to load

    # Click the top chat (dynamic adjustment)
    pyautogui.click(x=300, y=200)  # Adjust these coordinates for the first search result
    time.sleep(2)

    # Click the message input field
    pyautogui.click(x=500, y=700)  # Adjust these coordinates to the input field
    time.sleep(1)

    # Get the current time
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Prepare the message with emojis
    message = f"🚨 Alert! Someone is within 40 cm of the system at {current_time}. 😟 🚶‍♂👀"
    pyperclip.copy(message)  # Copy the message with emojis to the clipboard

    # Paste the message into WhatsApp
    pyautogui.hotkey("ctrl", "v")
    time.sleep(1)

    # Send the message (press Enter)
    pyautogui.press("enter")
    print(f"Message sent successfully to {recipient_phone_number}! 🚀")

    # Close WhatsApp
    time.sleep(1)
    pyautogui.hotkey("alt", "f4")
    print("WhatsApp closed.")

    # Exit the program after sending the message
    print("Exiting program.")
    exit()

# Monitor distance from Arduino
try:
    while True:
        if arduino.in_waiting > 0:
            distance = float(arduino.readline().decode().strip())
            print(f"Distance: {distance} cm")

            # Trigger actions if distance is below the threshold
            if distance < threshold_distance:
                print("Object too close! Closing app and sending WhatsApp message...")

                close_current_app()        # Close the currently active app
                send_whatsapp_message()    # Send WhatsApp message
                
                # The script will exit after sending the message.
except KeyboardInterrupt:
    print("Program terminated.")