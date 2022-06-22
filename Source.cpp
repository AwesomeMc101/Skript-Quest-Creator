// Skript Quest Creator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

namespace Writers
{
    void writeVariables(std::vector<std::string>& skriptLines, std::string mq)
    {
        skriptLines.push_back("variables:");
        skriptLines.push_back("    {%player%::" + mq + "started} = false");
        skriptLines.push_back("    {%player%::" + mq + "completed} = false");
    }

    void writeStart(std::vector<std::string>& skriptLines, std::string mq, std::string beginMsg)
    {
        skriptLines.push_back("function start"+mq+"(P: Player):");
        skriptLines.push_back("    message \"" + beginMsg + "\" to {_P}");
        skriptLines.push_back("    set {%{_P}%::" + mq + "started} to true");
    }

    void deciperRequirementType(std::vector<std::string>& skriptLines, std::string mq, int reqType, std::string toDoOnComplete, std::string toDoOnFalse)
    {
        std::cout << "\n\nRequirement Creator" << std::endl;
        std::string requirementLine = "";
        if (reqType == 1)
        {
            std::cout << "'custom' Item or 'vanilla' item requirement? " << std::endl;
            std::string onetype = "";
            std::getline(std::cin, onetype);
            if (onetype == "custom" || onetype == "Custom")
            {
                std::string itemTypeVanilla = "";
                std::string itemName = "";
                int itemCount = 0;
                std::cout << "What item must they have? " << std::endl;
                std::getline(std::cin, itemTypeVanilla);
                std::cout << "What must the item be called? " << std::endl;
                std::getline(std::cin, itemName);
                std::cout << "How many? " << std::endl;
                std::cin >> itemCount;

                skriptLines.push_back("function end" + mq + "(P: Player):");
                skriptLines.push_back("    set {_TEMPV} to amount of " + itemTypeVanilla + " named \""+itemName+"\" in {_P}'s inventory");
                skriptLines.push_back("    if {_TEMPV} >= " + std::to_string(itemCount) + ":");
                skriptLines.push_back("        set {%{_P}%::" + mq + "started} to false");
                skriptLines.push_back("        set {%{_P}%::" + mq + "completed} to true");
                skriptLines.push_back("        " + toDoOnComplete);
                skriptLines.push_back("    else:");
                skriptLines.push_back("            message \"" + toDoOnFalse + "\" to {_P}");
            }
            else
            {
                std::string itemTypeVanilla = "";
                int itemCount = 0;
                std::cout << "What item must they have? " << std::endl;
                std::getline(std::cin, itemTypeVanilla);
                std::cout << "How many? " << std::endl;
                std::cin >> itemCount;

                skriptLines.push_back("function end" + mq + "(P: Player):");
                skriptLines.push_back("    set {_TEMPV} to amount of " + itemTypeVanilla + " in {_P}'s inventory");
                skriptLines.push_back("    if {_TEMPV} >= "+std::to_string(itemCount)+":");
                skriptLines.push_back("        set {%{_P}%::" + mq + "started} to false");
                skriptLines.push_back("        set {%{_P}%::" + mq + "completed} to true");
                skriptLines.push_back("        " + toDoOnComplete);
                skriptLines.push_back("    else:");
                skriptLines.push_back("        message \"" + toDoOnFalse + "\" to {_P}");

            }
        }
    }
}

int main()
{
    while (1)
    {
        std::vector<std::string> skriptLines;
        std::string qName = "";
        std::string mqName = "";
        std::string beginMsg = "";

        std::string strReq = "";
        unsigned short reqType = 0;
        std::string toDoOnComplete = "";
        std::string toDoOnFalse = "";

        std::cout << "Quest Name? " << std::endl;
        std::getline(std::cin, qName);

        std::cout << "\nMini-Name for Skript? " << std::endl;
        std::getline(std::cin, mqName);
        Writers::writeVariables(skriptLines, mqName);

        std::cout << "\nBegin Quest Message? " << std::endl;
        std::getline(std::cin, beginMsg);
        Writers::writeStart(skriptLines, mqName, beginMsg);

        std::cout << "\nRequirement Type? Type List:\n1 = Item Requirement\nMore Coming\n " << std::endl;
        std::getline(std::cin, strReq);
        reqType = std::stoi(strReq);

        std::cout << "\nIf true, what should it do? Write Skript code for this, automatic version coming soon!" << std::endl;
        std::getline(std::cin, toDoOnComplete);

        std::cout << "\nIf false, what should we tell the player to do? " << std::endl;
        std::getline(std::cin, toDoOnFalse);

        Writers::deciperRequirementType(skriptLines, mqName, reqType, toDoOnComplete, toDoOnFalse);

        std::cout << "-----------------Your Code---------------\n\n";

        for (std::string line : skriptLines)
        {
            std::cout << line << std::endl;
        }

    }
}
