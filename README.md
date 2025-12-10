# TimeGuard-Access-Shield---Password-Controlled-Time-Restricted-Machine-Operation-System
📘 Project Explanation – TimeGuard Access Shield

My code implements the embedded firmware for TimeGuard Access Shield, a password-controlled, time-restricted device access system. The system uses an LPC2148 ARM7 processor, a 4×4 keypad, a 16×2 LCD, and the inbuilt RTC to enforce secure access to a machine or device. The firmware continually displays the real-time clock and allows the user to operate the device only after a valid password is entered and only during the allowed time window (S_TIME to E_TIME). All system settings—including password, RTC date/time, and machine working hours—can be configured through a menu activated by a hardware switch interrupt. 

At startup, the system initializes the LCD, keypad, RTC, and interrupts using init_system(). The main loop displays the continuously updated RTC time and date using DisplayRTCTime() and DisplayRTCDate(). If the user presses the entry key (* or external switch ENT_SW), the system either requests password authentication or enters the configuration menu. This interaction loop ensures the device remains secure at all times and reacts only to valid user actions.

Once the user attempts to access the machine, the program calls the password() function, which reads masked keypad input using readpassword(). The entered password is compared with the stored password ORG_P[]. If the password is correct and the current hour falls between S_TIME and E_TIME, the device is allowed to turn ON. The LED blinking block in your code visually indicates successful authentication, reinforcing both usability and security. If the password is incorrect or the time is outside the allowed range, the system denies access and displays an appropriate message. 

Configuration mode is handled by the function open_edit_menu(). When the interrupt switch is pressed, the system pauses normal operation and displays a menu that allows four operations: password change, RTC edit, machine start/end time edit, and exit. Each option opens a dedicated routine. For example, changetime() updates RTC hours/minutes/seconds, changedate() updates date/month/year with validation, and changeday() updates RTC weekday. All values entered through keypad are validated for correctness before being written to RTC registers, preventing invalid configuration.

The password-changing procedure is implemented in changepassword(). First, the system verifies the old password entered by the user. Then it collects a new password and asks for confirmation. Only if both match is the new password stored in ORG_P[]. The use of temporary buffers TMP_P[] and CNT_P[] ensures that incorrect or mismatched inputs do not overwrite the original password. 

The machine-time editing block (changemachinetime()) updates the allowed operating window (S_TIME and E_TIME). The routine prevents accidental changes by accepting values only between 1–23 hours. If an invalid entry is detected, the system displays an error message without updating the old stored time. The separation of display, validation, and assignment makes the code reliable for real environments such as labs, workshops, or restricted-operation equipment, as described in the project .

Overall, your code implements a complete embedded security and scheduling framework: live RTC display, password authentication, secure editable system parameters, and time-restricted device activation. The entire design follows the operational flow and requirements defined in the "TimeGuard Access Shield" specification you provided. 

This makes your project suitable for real-world usage where controlled machine access is mandatory.

📊 Block Diagram 1 – System Architecture
