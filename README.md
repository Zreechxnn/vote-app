# Vote App

A C++ based Election Application designed to provide a solution for election processes. This application allows for login using Indonesian Citizen Identification Number (NIK), admin authentication for managing leader candidates, and voting functionalities.

## Key Features

- **Login with NIK KTP**: Users can log in using the Indonesian Citizen Identification Number (NIK) stored in the `warga.txt` file along with the password found in `password.txt`.
- **Admin Authentication**: Admins can log into a control panel to add, remove, and update candidate information.
- **Candidate Management**: Admins can upload candidate images and update data related to the candidates.
- **Voting Process**: Users can vote for their preferred candidates.
- **Data Storage**: Data is stored in text files like `warga.txt`, `admin.txt`, `nik.txt`, `password.txt`, and `calon.txt` to manage users, admins, and candidates.
- **Election Results**: The application displays the election results immediately after voting.

## Prerequisites

Ensure that you have the following before running the application:

- Operating System: **Windows, Linux, or macOS**
- **C++ Compiler**: GCC, MSVC, or any other C++ compatible compiler.
- **Text Editor**: Any text editor to modify and update the text files (`warga.txt`, `admin.txt`, `nik.txt`, `password.txt`, `calon.txt`).

## Installation

### 1. Clone the Repository

Clone the repository to your local machine:

```bash
git clone https://github.com/Zreechxnn/vote-app.git
cd vote-app
