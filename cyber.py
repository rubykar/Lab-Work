import os
import subprocess
import time

def monitor_usb():
    while True:
        # List connected USB devices
        result = subprocess.run(["lsusb"], stdout=subprocess.PIPE, text=True)
        connected_devices = result.stdout.lower()

        # Check for a specific USB device identifier (customize based on your device)
        if "your_usb_device_identifier" in connected_devices:
            print("USB device detected!")
            lock_usb_device()
        else:
            print("No USB device detected.")

        time.sleep(5)  # Adjust the interval as needed

def lock_usb_device():
    # Implement the logic to lock the USB device (e.g., unmount or disable)

    # For Linux, you can unmount the device
    os.system("sudo umount /dev/sdX")  # Replace /dev/sdX with the appropriate device path

    print("USB device locked!")

if __name__ == "__main__":
    monitor_usb()
