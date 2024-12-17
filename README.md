Vote App - Pemilu Election Application
A C++ based Election Application designed to provide a solution for election processes. This application allows for login using Indonesian Citizen Identification Number (NIK), admin authentication for managing leader candidates, and voting functionalities.



Key Features
Login with NIK KTP: Users can log in using the Indonesian Citizen Identification Number (NIK) stored in the warga.txt file along with the password found in password.txt.
Admin Authentication: Admins can log into a control panel to add, remove, and update candidate information. (coming soon)
Candidate Management: Admins can upload candidate images and update data related to the candidates. (coming soon)
Voting Process: Users can vote for their preferred candidates.
Data Storage: Data is stored in text files like warga.txt, admin.txt, nik.txt, password.txt, and calon.txt to manage users, admins, and candidates.
Election Results: The application displays the election results immediately after voting.
Prerequisites
Ensure that you have the following before running the application:

Operating System: Windows, Linux, or macOS
C++ Compiler: GCC, MSVC, or any other C++ compatible compiler.
Text Editor: Any text editor to modify and update the text files (warga.txt, admin.txt, nik.txt, password.txt, calon.txt).
Installation
1. Clone the Repository
Clone the repository to your local machine:

bash
Copy code
git clone https://github.com/Zreechxnn/vote-app.git
cd vote-app
2. Build the Application
On Windows, you can use Microsoft Visual Studio or MinGW.
On Linux/macOS, you can use GCC.
For example, on Linux or macOS, you can build the application by running:

bash
Copy code
g++ -o vote-app main.cpp
3. Modify Text Files
Make sure you have the following text files properly populated:

warga.txt: Contains the list of registered users with their NIK.
password.txt: Contains the corresponding passwords for users.
calon.txt: Contains a list of candidates, including their names and descriptions.
Optionally, you can create admin.txt and store admin data for authentication.

4. Run the Application
After building the application, run it:

bash
Copy code
./vote-app
Usage
Login: Users can log in with their valid NIK and password.
Voting: After logging in, users can select a candidate to vote for.
Admin Features: Admin login is partially implemented; features like adding/removing candidates and uploading images are planned for future updates.
Let me know if you need further updates or adjustments!
