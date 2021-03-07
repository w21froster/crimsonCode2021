# Crimson Code 2021
### Port Scanner for IPv4/IPv6

### Preface
- In the era of COVID-19, more people than ever are working from home and accessing their companie's network remotely. Network Administrators are hastily implementing VPNs and firewall rules to allow their company's employees to login. This is perfect for productivity, but what about security? What happens when the wrong SSH port gets exposed to the internet? This is where our port scanner comes into focus. We can scan any target with an IPv4/IPv6 address and tell you which ports are open. This helps make informed decisions about the security of your PC or network in this connected world.

### Libraries Used
- Boost library (ASIO) https://www.boost.org/doc/libs/1_75_0/doc/html/boost_asio.html
### Features

- Accepts IPv4 addresses and IPv6 addresses for targets
- Scan against a list of wellknown ports or input a custom port
- TCP only as of now

### Build Instructions

- Clone the repository
- Navigate to testPort/testPort
- Build from solution file testPort.sln (VS19)

### To Do
| Feature  | Status  |
| ------------ | ------------ |
| Accept list of IP addresses |  Not Started |
| Color the status of each port (green for unblocked, red for blocked) |  Not Started |

### Preview
![alt text](https://raw.githubusercontent.com/w21froster/crimsonCode2021/main/screenshots.gif)

### Credits
- Zakiya Pruitt 
- Kyle Parker
- William Foster
