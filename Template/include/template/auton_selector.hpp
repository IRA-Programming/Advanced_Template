#pragma once
#include "template_api.hpp"
#include <vector>
#include <algorithm>

namespace adt {
    class AutonSelector;

    class Autons{
        public:
            Autons() = default;
            Autons(std::function<void()> auton, std::string name = "\0", std::string shortHandIdentifier = "\0") : 
                _auton(auton), 
                _name(name),
                _shortHandIdentifier(shortHandIdentifier) {
                    if (_shortHandIdentifier == "\0"){
                        std::vector<char> possibleIdentifiers = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
                        if(usedShortHandIdentifiers.size() <= 26){
                            _shortHandIdentifier = possibleIdentifiers[usedShortHandIdentifiers.size()];
                            usedShortHandIdentifiers.push_back(_shortHandIdentifier);
                        }else{
                            int i = static_cast<int>((log(usedShortHandIdentifiers.size()))/log(26));
                            int j = static_cast<int>((log(usedShortHandIdentifiers.size()) - 1)/log(26));
                            if(i > j){
                                std::vector<char> characters;
                                for(int k = 0; k < i; k++){
                                    characters.push_back('A');
                                }
                                std::string identifier(characters.begin(), characters.end());
                                _shortHandIdentifier = identifier;
                            }else{
                                std::string lastIdentifier = usedShortHandIdentifiers.back();
                                std::string flippedIdentifier(lastIdentifier.rbegin(), lastIdentifier.rend());
                                std::vector<char> characters(flippedIdentifier.begin(), flippedIdentifier.end());
                                int spot = 0;
                                for (char &c : characters){
                                    if(c != 'Z'){
                                        auto it = std::find(possibleIdentifiers.begin(), possibleIdentifiers.end(), c);
                                        if(it != possibleIdentifiers.end()){
                                            c = possibleIdentifiers[std::distance(possibleIdentifiers.begin(), it) + 1];
                                            characters[spot] = c;
                                            break;
                                        }
                                    }else{
                                        characters[spot] = 'A';
                                        spot++;
                                        continue;
                                    }
                                }
                                std::string identifier(characters.rbegin(), characters.rend());
                                _shortHandIdentifier = identifier;
                            }
                        }
                    }

                    if(name == "\0"){
                        _name = "Auton " + _shortHandIdentifier;
                    }
                }

            struct AutonReturnType{
                std::string asName;
                std::string asIdentifier;
                std::function<void()> asRaw;
            };

            AutonReturnType getAutonStructure() const {
                return AutonReturnType{_name, _shortHandIdentifier, _auton};
            }
            
            void run(){
                _auton();
            }
        private:
            std::function<void()> _auton;
            std::string _name;
            std::string _shortHandIdentifier;
            inline static std::vector<std::string> usedShortHandIdentifiers = {};
            
            friend class AutonSelector;

    };

    class AutonSelector {
        public:
            AutonSelector(vex::controller controller, std::vector<Autons> autons) : autons(autons) {}

            struct FullReturnType{
                Autons::AutonReturnType asAutonReturnType;
            };

            static FullReturnType assemble(std::function<Autons::AutonReturnType(void)> autonselector){
                Autons::AutonReturnType _asAutonReturnType = autonselector();
                return FullReturnType{_asAutonReturnType};

            }

            Autons::AutonReturnType AutonSelector1();

            //Complex Selector
            void addAuton(Autons auton) {
                autons.push_back(auton);
            }

            enum class setButtonType{
                SELECT,
                NOAUTON
            };

            void setButton(vex::controller::button &button, setButtonType type) {
                switch (type){
                    case setButtonType::SELECT:
                        selectButton = button;
                        break;
                    case setButtonType::NOAUTON:
                        noAutonButton = button;
                    default:
                        break;
                }
            }

            void runSelectedAuton() {
                selectedAuton.run();
            }

            enum class AutonReturnType{
                name,
                shortHandIdentifier,
                raw
            };


        private:
            std::vector<Autons> autons;
            vex::controller::button selectButton;
            vex::controller::button noAutonButton;
            vex::controller controller;
            Autons selectedAuton;
    };
} // namespace adt
