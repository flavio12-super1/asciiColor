#include <iostream>
#include <termios.h>
#include <unistd.h>

void setNonCanonicalMode()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void restoreTerminalMode()
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void displayColorOptions(int selectedOption)
{
    const char *colorOptions[] = {
        "\033[1;31m[red]\033[0m",     // Red
        "\033[1;33m[yellow]\033[0m",  // Yellow
        "\033[1;35m[Magenta]\033[0m", // Magenta
        "\033[1;32m[green]\033[0m",   // Green
        "\033[1;34m[blue]\033[0m"     // Blue
    };

    for (int i = 0; i < 5; ++i)
    {
        if (i == selectedOption)
        {
            std::cout << "\033[1;37;41m" << colorOptions[i] << "\033[0m ";
        }
        else
        {
            std::cout << colorOptions[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main()
{

    std::string colors[5] = {
        "31", // Red
        "33", // Orange
        "35", // Magenta
        "32", // Green
        "34"  // Blue
    };

    setNonCanonicalMode();

    int selectedOption = 0;

    while (1)
    {
        std::system("clear");
        displayColorOptions(selectedOption);

        char c;
        std::cin.get(c);

        if (c == 27)
        { // Escape key
            std::cin.get(c);
            if (c == '[')
            {
                std::cin.get(c);
                switch (c)
                {
                case 'B': // Down arrow
                    selectedOption = (selectedOption - 1 + 5) % 5;
                    break;
                case 'A': // Up arrow
                    selectedOption = (selectedOption + 1) % 5;
                    break;
                case 'C': // Right arrow
                    selectedOption = (selectedOption + 1) % 5;
                    break;
                case 'D': // Left arrow
                    selectedOption = (selectedOption - 1 + 5) % 5;
                    break;
                }
            }
        }

        if (c == '\n')
        {
            std::cout << "Selected option: " << selectedOption << std::endl;
            break;
        }
    }

    restoreTerminalMode();
    // std::string color = "\033[" + colors[selectedOption] + ";5;2m";
    std::string color = "\033[1;" + colors[selectedOption] + "m";
    std::cout << color << "hello world"
              << "\033[0m" << std::endl;
    return 0;
}
