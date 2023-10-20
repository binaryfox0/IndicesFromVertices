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

std::vector<int> search(const std::vector<std::vector<std::wstring>> vector)
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
    std::vector<std::vector<std::wstring>> vector_vertices, modified_vector;
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

    std::vector<std::wstring> text;


    std::cout << "Copy your vertices here: " << std::endl;
    int emptyLines = 0; // Counter for empty lines

    while (true) {
        std::wstring input;

        std::getline(std::wcin, input);

        if (input.empty()) {
            emptyLines++;
            if (emptyLines == 2) {
                std::cout << "Please wait..." << std::endl;
                break;
            }
        } else {
            emptyLines = 0;
            text.push_back(input);
        }
    }

    for (auto& a : text)
    {
        a.erase(std::remove(a.begin(), a.end(), '\t'), a.end());
        a.erase(std::remove(a.begin(), a.end(), ' '), a.end());
        if(a == L"\n") text.erase(std::remove(text.begin(), text.end(), a), text.end());

        std::vector<std::wstring> row;
        std::wstringstream ss(a);

        std::wstring token;
        while (std::getline(ss, token, L',')) {
            // Convert string token to float
            try {
                row.push_back(token);
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

    // Remove duplicate vector
    while(1)
    {
        std::vector<int> find_index = search(modified_vector);
        modified_vector.erase(modified_vector.begin() + find_index[0]);

        find_index = search(modified_vector);
        if(find_index.empty()) break;
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
            if(j[0] != L'-') std::wcout << L' ';
            std::wcout << j << ", ";
        }
        std::cout << "\n";
    }

    // Generate indices from vertices
    // Calculate the number of split vectors and the number of rows for each split vector
    int numSplitVectors = 2; // Desired number of split vectors
    int Rows = vector_vertices.size() / numSplitVectors;

    // Create a 3D vector to store the split vectors
    std::vector<std::vector<std::vector<std::wstring>>> splitVector3D(numSplitVectors);

    // Split the original vector and store the split vectors in the 3D vector
    for (int i = 0; i < numSplitVectors; ++i) {
        std::vector<std::vector<std::wstring>> splitVector(vector_vertices.begin() + i * Rows, vector_vertices.begin() + (i + 1) * Rows);
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