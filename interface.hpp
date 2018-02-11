/**
 *    @author Team 3
 *    @date
 *    @file interface.hpp
 */


Interface::Interface()
{

}


Interface::~Interface()
{

}

void Interface::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

std::string Interface::getInput(const char *message)
{

    std::string inputString;

    std::cout << message;
    getline(std::cin, inputString);

    return inputString;
}


void Interface::Wait(std::string wait_string)
{
    std::cout << wait_string;
    std::cout << "\nPress Enter to continue...\n";
    getchar();
}


Interface::Menu::Menu(const std::vector<std::pair<std::string, void (*)()>> &options)
{
    option_list = options;
}


void Interface::Menu::Loop()
{
    while (true)
    {
        clearScreen();

        //Draw the menu
        Draw();

        //Get user selection
        auto key = getInput("\nMenu -> ");

        unsigned int pos = atoi(key.c_str());

        //If input is valid
        if( pos <= option_list.size() && pos > 0)
        {
            //.second is the second element of the pair of the vector element
            auto func_ptr = (option_list[pos-1].second);

            //If the func_ptr is a nulllptr then we exit the program (exit option)
            if (func_ptr == nullptr)
            {
                break;
            }
            else
            {
                func_ptr();
            }
        }
        else
        {
            clearScreen();
            Header();

            std::cout << "\nThis option is not valid." << std::endl;
            Wait("");
        }
    }
}

void Interface::Menu::Draw()
{
    std::string SOMETHING = "";

    Header();

    for (size_t i = 0; i < option_list.size(); ++i)
        std::cout << "\n(Press " << i+1 << ")    " << option_list[i].first;

}

void Interface::Menu::Header()
{

    std::cout << "***************************************************************************\n";
    std::cout << " ______               _      _____      _              _       _           \n"
    "|  ____|             | |    / ____|    | |            | |     | |          \n"
    "| |____   _____ _ __ | |_  | (___   ___| |__   ___  __| |_   _| | ___ _ __ \n"
    "|  __\\ \\ / / _ \\ '_ \\| __|  \\___ \\ / __| '_ \\ / _ \\/ _` | | | | |/ _ \\ '__|\n"
    "| |___\\ V /  __/ | | | |_   ____) | (__| | | |  __/ (_| | |_| | |  __/ |   \n"
    "|______\\_/ \\___|_| |_|\\__| |_____/ \\___|_| |_|\\___|\\__,_|\\__,_|_|\\___|_|" << std::endl;
    std::cout << "\n***************************************************************************\n";
    std::cout << "   Developed by: Team 3 \tEECS 443 \tProject 1 \tKU - 2018\n";
    std::cout << "***************************************************************************\n";
    std::cout << "        All times displayed are CDT (Central Daylight Time)\n";
    std::cout << "***************************************************************************\n\n";

    /*ADD SECTION PRINTING ALL EVENT LIST FILE ENTRIES -> USE IO*/
    IO io("event.list");
    io.displayEntries();

    std::cout << "***************************************************************************";
}

void Interface::toggleTimeFormat()
{
    IO io("event.list");

    if( io.timeFormat == false )
        io.timeFormat = true;
    else
        io.timeFormat = false;
}
