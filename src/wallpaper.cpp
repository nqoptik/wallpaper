#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{
    int default_duration = 600;
    int minimum_duration = 5;
    int duration = default_duration;
    if (argc == 2)
    {
        duration = atoi(argv[1]);
        if (duration < minimum_duration)
        {
            duration = minimum_duration;
        }
    }

    std::string current_path = boost::filesystem::current_path().string();
    std::vector<std::string> file_path_list;
    std::string wallpapers_folder = current_path + "/wallpapers";
    if (!boost::filesystem::is_directory(wallpapers_folder))
    {
        std::cout << wallpapers_folder << " is not a directory.\nCould not set up wallpaper!" << std::endl;
    }
    else
    {
        for (auto const& entry : boost::filesystem::recursive_directory_iterator(wallpapers_folder))
        {
            if (!boost::filesystem::is_directory(entry.path()))
            {
                if ((entry.path().string().find(".jpg") != std::string::npos) ||
                    (entry.path().string().find(".png") != std::string::npos))
                {
                    file_path_list.push_back(entry.path().string());
                }
            }
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        std::random_shuffle(file_path_list.begin(), file_path_list.end());
    }

    for (size_t i = 0; i < file_path_list.size(); ++i)
    {
        std::cout << file_path_list[i] << std::endl;
    }

    std::ofstream output_xml("wallpaper.xml");
    output_xml << "<background>\n";
    for (size_t i = 0; i < file_path_list.size(); ++i)
    {
        output_xml << "    <static>\n";
        output_xml << "        <duration>" << duration << ".00</duration>\n";
        output_xml << "        <file>" << file_path_list[i] << "</file>\n";
        output_xml << "    </static>\n";
    }
    output_xml << "</background>\n";
    output_xml.close();

    return 0;
}
