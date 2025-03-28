#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

static inline std::vector<float> parse_line(const std::string& str)
{
    std::vector<float> out;
    std::stringstream ss(str);
    std::string token;
    while(std::getline(ss, token, ','))
    {   
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end()); // Remove spaces
        if (!token.empty() && token.back() == 'f') {
            token.pop_back(); // Remove 'f' suffix
        }
        try {
            out.push_back(std::stof(token));
        }
        catch(const std::exception& e) {
            std::cerr << "Invalid token \"" << token << "\". Skipping...\n";
        }
        
    }
    return out;
}

std::vector<std::vector<float>> convert_multi(
    const std::vector<float>& input, const int el_vertex)
{
    int vec_count = input.size() / el_vertex;
    std::vector<std::vector<float>> out;
    out.reserve(vec_count);
    auto begin = input.begin();
    for(int i = 0; i < vec_count; i++)
    {
        auto end = begin + el_vertex;
        out.emplace_back(begin, end);
        begin = end;
    }
    return out;
}

void generate_indices(
    const std::vector<float>& input,
    const int el_vertex,
    std::vector<int>& output_indices,
    std::vector<std::vector<float>>& output_vertices)
{
    std::vector<std::vector<float>> original = convert_multi(input, el_vertex);
    std::vector<std::vector<float>> unique_vertices;
    std::map<std::vector<float>, int> lookup;
    
    for (const auto& vertex : original) {
        if (lookup.find(vertex) == lookup.end()) {
            lookup[vertex] = unique_vertices.size();
            unique_vertices.push_back(vertex);
        }
        output_indices.push_back(lookup[vertex]);
    }
    output_vertices = unique_vertices;
}

int main()
{
    std::cout << "Paste your vertices below: " << std::endl;
    int counter = 0, el_vertex = 0; const int max_enter = 2;
    std::vector<float> input_vertices;
    while(counter < max_enter + 1)
    {
        std::string line;
        std::getline(std::cin, line);
        if(line.empty()) {
            counter++;
            if(counter == max_enter)
                std::cout << "Press enter one more to stop inputting....";
        } else {
            counter = 0;
            std::vector<float> tmp = parse_line(line);
            input_vertices.insert(input_vertices.end(), tmp.begin(), tmp.end());
        }
    }
    std::cout << "How many elements each vertex in vertices have ? ";
    std::cin >> el_vertex;
    if(el_vertex == 0) { std::cerr << "Impossible to have 0 element per vertex. Aborted.\n"; return 1; }
    if(input_vertices.size() % el_vertex) { std::cerr << "Invalid elements per vertex. Aborted.\n"; return 1; }
    
    std::vector<std::vector<float>> vertices;
    std::vector<int> indices;
    generate_indices(input_vertices, el_vertex, indices, vertices);
    
    std::cout << "New vertices below: " << std::endl;
    for(auto& a : vertices)
    {
        for(auto b : a)
            printf("%*s%f, ", b >= 0, "", b);
        printf("\n");
    }
    
    std::cout << "New indices below: " << std::endl;
    for(auto a : indices)
        printf("%d, ", a);
    printf("\n");
    
    return 0;
}
