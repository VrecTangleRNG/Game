This is my first repository containing my passion project.

For now, there is yet no name for this game, so i will call it anonymous racing game.
You can install and play this game (or even tweak the code inside the program) by following this guide below.

WHAT PROGRAMS DO YOU NEED BEFORE INSTALLING THIS PROGRAM:
- any terminal (mine is Windows terminal).
- git.
    If you don't have it, in your terminal, type "winget install git" and then follow its installation process.
- w64devkit (the gcc).
    Skip this process if you already have MINGW in your pc, otherwise go to your browser and search for "w64devkit" on github and follow its installation process.
    Or if want a simpler method, install WINGW into your pc by searching for it in your browser.

HOW TO INSTALL ANONYMOUS RACING GAME TO YOUR PC:
- go to your desired folder where you will put your game at.
    Open your teminal, then type "cd \[TARGETFOLDER]" where TARGETFOLDER is your desired target folder (case-sensitive i guess).
    This will put you into your desired directory path, rady to get the instalation folder.
- clone this repository.
    In the same terminal, type "git clone https://github.com/VrecTangleRNG/Game".
    This will retrieve all the folder present in this repository.
- go into Game\ directory.
    In the same terminal, type "cd Game".
    This will put you inside the Game directory. You might want to take a peek at files inside the folder by typing "ls -a".
- build the executable file.
    In that directory, type "make".
    You can see all the building process shown by your terminal.
- play the game.
    After building process finished with no error (if you see error(s), you can contact me through my socials), type "app\o" to open the game.
    Or if you prefer open it graphically, go into [TARGETFOLDER]\Game\app\. inside, you can see "o.exe", you can double tap it to open the game.

HOW TO CONTROL THE CAR:
- KEY_UP : Accelerate
- KEY_LEFT : Brake/decelerate
- KEY_D : Turn right
- KEY_A : Turn left
To pause the game, press KEY_ESCAPE

If you have anything to say (like feedback, request, or problems) you can freely contact me through my socials.
