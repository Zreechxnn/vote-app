 # Vote App

A C++ based Election Application designed to provide a solution for election processes. This application allows for login using Indonesian Citizen Identification Number (NIK), admin authentication for managing leader candidates, and voting functionalities.
![image](https://h.top4top.io/p_3273g6ky51.png)

## ⚠️ Disclaimer  

The code in this repository is intended **only for developers** with a basic understanding of programming. Please use it responsibly and for development purposes only.

- **Not recommended for direct use in production environments without thorough testing.**  
- No guarantees are provided regarding the absence of bugs or errors.  
- The author is not liable for any damages or issues caused

## Key Features

- **Login with NIK KTP**: Users can log in using the Indonesian Citizen Identification Number (NIK) stored in the warga.txt file along with the password found in password.txt.
- **Admin Authentication**: Admins can log into a control panel to add, remove, and update candidate information. (soon)
- **Candidate Management**: Admins can upload candidate images and update data related to the candidates. (soon)
- **Voting Process**: Users can vote for their preferred candidates.
- **Data Storage**: Data is stored in text files like warga.txt, admin.txt, nik.txt, password.txt, and calon.txt to manage users, admins, and candidates.
- **Election Results**: The application displays the election results immediately after voting.

## Prerequisites

Ensure that you have the following before running the application:

- Operating System: **Windows, Linux, or macOS**
- **C++ Compiler**: GCC, MSVC, or any other C++ compatible compiler.
- **Text Editor**: Any text editor to modify and update the text files (warga.txt, admin.txt, nik.txt, password.txt, calon.txt).

## Installation

### 1. Clone the Repository

Clone the repository to your local machine:

bash
git clone https://github.com/Zreechxnn/vote-app.git
cd vote-app
