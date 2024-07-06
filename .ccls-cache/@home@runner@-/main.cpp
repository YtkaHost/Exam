#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

void choose_hero(std::string &hero, const std::string &attribute,
                 const std::string &playstyle, const std::string &range_type,
                 const std::string &complexity);
std::string get_user_input(const std::string &text);
void user_choice();

const int MAX_HEROES = 128;

int main() {
  std::cout << "Hello, this program was created to help you choose a hero in "
               "the game Dota 2"
            << std::endl;
  std::cout << "Now you will be asked questions to choose a hero that at this "
               "moment is most suitable for you"
            << std::endl;
  std::cout << "P.S. This program was created without a Universal attribute "
               "due to a broken Dota Wiki ^~^"
            << std::endl;
  std::cout << std::endl;
  srand(time(NULL));
  user_choice();
  return 0;
}

void choose_hero(std::string &hero, const std::string &attribute,
                 const std::string &playstyle, const std::string &range_type,
                 const std::string &complexity) {
  std::ifstream hero_file("heroes.txt");

  std::string line;
  std::string *heroes = new std::string[MAX_HEROES];
  int num_heroes = 0;

  while (getline(hero_file, line)) {
    if (line.find(attribute) != std::string::npos &&
        line.find(playstyle) != std::string::npos &&
        line.find(range_type) != std::string::npos &&
        line.find(complexity) != std::string::npos) {
      if (num_heroes < MAX_HEROES) {
        heroes[num_heroes++] = line;
      } else {
        std::cout << "Maximum hero limit reached." << std::endl;
        break;
      }
    }
  }

  if (num_heroes == 0) {
    delete[] heroes;
    return;
  }

  int choice = rand() % num_heroes;
  hero = heroes[choice];

  delete[] heroes;
  hero_file.close();
}

std::string get_user_input(const std::string &text) {
  std::string input;
  std::cout << text;
  std::getline(std::cin, input);
  return input;
}

void user_choice() {
  std::set<std::string> valid_attributes = {"strength", "agility", "intellect"};
  std::set<std::string> valid_playstyles = {"carry", "support", "utility"};
  std::set<std::string> valid_range_types = {"melee", "ranged"};
  std::set<std::string> valid_complexities = {"easy", "medium", "hard"};

  std::string attribute;
  std::string playstyle;
  std::string range_type;
  std::string complexity;

  while (true) {
    attribute = get_user_input(
        "Choose the hero's attribute (strength, agility, intellect): ");
    if (valid_attributes.find(attribute) == valid_attributes.end()) {
      std::cout << "Invalid attribute. Please try again." << std::endl;
      continue;
    }

    playstyle = get_user_input(
        "Choose the hero's playstyle (carry, support, utility): ");
    if (valid_playstyles.find(playstyle) == valid_playstyles.end()) {
      std::cout << "Invalid playstyle. Please try again." << std::endl;
      continue;
    }

    range_type =
        get_user_input("Choose the hero's range type (melee, ranged): ");
    if (valid_range_types.find(range_type) == valid_range_types.end()) {
      std::cout << "Invalid range type. Please try again." << std::endl;
      continue;
    }

    complexity =
        get_user_input("Choose the hero's complexity (easy, medium, hard): ");
    if (valid_complexities.find(complexity) == valid_complexities.end()) {
      std::cout << "Invalid complexity. Please try again." << std::endl;
      continue;
    }

    break;
  }

  std::string hero;
  choose_hero(hero, attribute, playstyle, range_type, complexity);

  if (hero.empty()) {
    std::cout << "No hero found for the given criteria." << std::endl;
  } else {
    std::cout << "Chosen Hero: " << hero << std::endl;
  }
}
