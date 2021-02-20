#include <iostream>
#include <fstream>
#include <ctime>


std::string to_lower(std::string str) {
    for (char &ch : str) {
        ch = tolower(ch);
    };

    return str;
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        /* received no cli args */
        std::cout << "Specify arguements! Usage: '" << argv[0] 
                  << " <file_name[, file_name]>'\n";
        return 1;
    }

    std::string domain;
    size_t pos { 0 };
    size_t pos1 { 0 };

    unsigned int count { 0 };
    unsigned int count_files { 0 };

    time_t _time { time(0) };

    /* for loop to iterate if they supply more than 1 file */
    for (int i { 1 }; i < argc; ++i && ++count_files) {
        std::ifstream file(argv[i]);

        if (file.is_open()) {
            std::string line;

            while (std::getline(file, line)) { 
                if ((pos = line.find(":")) != std::string::npos && (pos1 = line.find("@")) != std::string::npos) {
                    /* extract domain */
                    domain = to_lower(line.substr(pos1 + 1, pos - pos1 - 1));

                    std::ofstream File("sorted/" + domain + ".txt", std::ios_base::app);
                    File << line << '\n';
                    count += 1;

                    /* close after done */
                    File.close();
                }
            }

            /* close after done */
            file.close();
        }
    }

    time_t __time { time(0) - _time };
    std::cout << "Sorted " << count_files << " file(s) and " << count 
              << " line(s) in " <<  __time << " seconds | ";

    if (__time > 0) {
        std::cout << count / __time << " lines/s\n";
    } else {
        std::cout << count << " lines/s\n";
    }
}
