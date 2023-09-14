#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

/*
float vertices[] = 
{
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f,  
    0.5f, -0.5f, 0.0f,  
   -0.5f, -0.5f, 0.0f,  
   -0.5f,  0.5f, 0.0f   
};
*/
std::wstring float2wstr(float number)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(1) << number;

    std::wstring str = ss.str();

    return str;
}

std::vector<int> search(const std::vector<std::vector<float>> vector)
{
    std::vector<int> index;
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = i + 1; j < vector.size(); j++)
        {
            if (vector[j] == vector[i] && j != i)
                index.push_back(j);
        }
    }
    return index;
}

int main()
{
    std::vector<std::vector<float>> vector_vertices, modified_vector;
    /*
    int numColumns = 3, numRows = sizeof(vertices) / sizeof(float) / numColumns;
    for (int row = 0; row < numRows; row++)
    {
        std::vector<float> vecCol;
        for (int col = 0; col < numColumns; col++)
        {
            vecCol.push_back(vertices[row * numColumns + col]);
        }
        vector_vertices.push_back(vecCol);
    }
    */

    std::vector<std::string> text;


    std::cout << "Copy your vertices here: " << std::endl;
    while (true) {
        std::string input;

        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Processing input vertices..." << std::endl;
            break;
        } else {
            text.push_back(input);
        }
    }

    for (auto& a : text)
    {
        a.erase(std::remove(a.begin(), a.end(), '\t'), a.end());
        a.erase(std::remove(a.begin(), a.end(), ' '), a.end());

        std::vector<float> row;
        std::stringstream ss(a);

        std::string token;
        while (std::getline(ss, token, ',')) {
            // Convert string token to float
            try {
                float value = std::stof(token);
                row.push_back(value);
            } catch (const std::exception& e) {
                std::cout << "Error: Out of range value encountered. Please enter a valid floating-point number." << std::endl;
                return 1;
            }
        }

        vector_vertices.push_back(row);
    }

    for(auto a : vector_vertices)
    {
        a.erase(a.begin() + 3, a.end());
    }

    modified_vector = vector_vertices;

    // Generate new vertices to use with indices
    std::vector<int> index = search(modified_vector);
    for (int i = static_cast<int>(index.size()) - 1; i >= 0; i--)
    {
        int a = index[i];
        modified_vector.erase(modified_vector.begin() + a);
    }

    if (modified_vector.empty()) {
        std::cout << "Error: No valid vertices found. Please make sure the input generates valid vertices." << std::endl;
        return 1;
    }

    std::cout << "New vertices using with indices" << std::endl;
    for (auto i : modified_vector)
    {
        for (auto j : i)
        {
            std::wstring text = float2wstr(j) + L"f";
            if (text[0] != '-') std::cout << " ";
            std::wcout << text << ", ";
        }
        std::cout << "\n";
    }

    // Generate indices from vertices
    // Calculate the number of split vectors and the number of rows for each split vector
    int numSplitVectors = 2; // Desired number of split vectors
    int Rows = vector_vertices.size() / numSplitVectors;

    // Create a 3D vector to store the split vectors
    std::vector<std::vector<std::vector<float>>> splitVector3D(numSplitVectors);

    // Split the original vector and store the split vectors in the 3D vector
    for (int i = 0; i < numSplitVectors; ++i) {
        std::vector<std::vector<float>> splitVector(vector_vertices.begin() + i * Rows, vector_vertices.begin() + (i + 1) * Rows);
        splitVector3D[i] = splitVector;
    }

    std::vector<std::vector<unsigned int>> indices;
    for (size_t i = 0; i < splitVector3D.size(); ++i)
    {
        std::vector<unsigned int> row;
        for (int j = 0; j < splitVector3D[i].size(); ++j)
        {
            for (int k = 0; k < modified_vector.size(); ++k)
            {
                if (splitVector3D[i][j] == modified_vector[k]) row.push_back(k);
            }
        }
        indices.push_back(row);
    }

    std::cout << "New indices" << std::endl;
    for (auto i : indices)
    {
        for (auto j : i)
        {
            std::cout << j << ", ";
        }
        std::cout << "\n";
    }

    return 0;
}