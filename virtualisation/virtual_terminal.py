import pty
import os

# Create a virtual terminal
master_fd, slave_fd = pty.openpty()

# Run a command in the virtual terminal
commands = ["touch test.txt", "ls -l"]

for command in commands:
    fcommand = f"{command}\n"
    byte_command = fcommand.encode()
    os.write(master_fd, byte_command)

# Read the output
output = os.read(master_fd, 1024)
print(output.decode())

# Close the virtual terminal
os.close(master_fd)
os.close(slave_fd)
