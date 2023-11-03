## Getting started
### Setting up VirtualBox
In VirtualBox, go to File > Host Network Manager. If you see a VirtualBox Host-Only Ethernet Adapter listed, you're set. Otherwise, make one using the Create button.

Create a new VM with New. Give it a name, select Type: Linux and Version: Ubuntu, leave the default settings.

Select your new VM, click Settings, and go to Network. If it's not already done, enable Enable Network Adapter, select Attached-to: Host-Only Adapter and make sure Name: points to the network you made earlier (probably VirtualBox Host-Only Ethernet Adapter)

### Starting the VM
Download the .iso file from the intranet's project page.

Now, Start the VM. It'll prompt you for an image to boot from. Import the ISO with the folder button, select it, and start the VM.

### Connecting
SnowCrash should now boot and display ASCII art, an IP address and prompt you for a login.

Now, disregard that, and copy the IP address displayed. If you've correctly setup the network, you should be able to SSH into rainfall.

You can now log in remotely :
```ssh level0@<IP_ADDRESS> -p 4242```

breakpoints: b *addr and b function
move: nexti, stepi
run: r, r $(CMD), r < file