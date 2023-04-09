    #pragma once
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <cstdlib>
    #include <ctime>
    #include <string>
    using namespace std;

    vector<pair<string, string>> elegir_pares_aleatorios(const vector<string>& A, int num_pares)
    {
        vector<pair<string, string>> pares;
        srand(time(NULL));
        while (pares.size() < num_pares) 
        {
            int i = rand() % A.size();
            int j = rand() % A.size();
            auto p = make_pair(A[i], A[j]);
            auto it = find(pares.begin(), pares.end(), p);
            if (it == pares.end()) {
                pares.push_back(p);
            }
        }
        return pares;
    }

    void verificar_propiedades(vector<pair<string, string>> pares, vector<string> A) 
    {
        bool reflexiva = true;
        bool irreflexiva = true;
        bool simetrica = true;
        bool asimetrica = true;
        bool antisimetrica = true;
        bool transitiva = true;
        bool equivalencia = true;
        bool orden_parcial = true;

        bool diagonal_presente = false;
        if (!A.empty()) {
            for (auto a : A) {
                if (find(pares.begin(), pares.end(), make_pair(a, a)) == pares.end()) {
                    reflexiva = false;
                    irreflexiva = false;
                    diagonal_presente = false;
                    break;
                }
                diagonal_presente = true;
            }
        }
        else {
            irreflexiva = true;
            diagonal_presente = false;
        }


        // Verificar simetría y antisimetría
        for (auto p : pares)
        {
            if (find(pares.begin(), pares.end(), make_pair(p.second, p.first)) == pares.end()) {
                simetrica = false;
                antisimetrica = true;
            }
            if (p.first != p.second &&
                find(pares.begin(), pares.end(), make_pair(p.second, p.first)) != pares.end()) {
                antisimetrica = false;
            }
        }

        // Verificar asimetría
        for (auto p : pares) {
            if (p.first == p.second) {
                asimetrica = false;
            }
        }

        // Verificar transitividad
        for (auto a : A) {
            for (auto b : A) {
                for (auto c : A) {
                    if (a != b && b != c && a != c) {
                        if (find(pares.begin(), pares.end(), make_pair(a, b)) != pares.end() &&
                            find(pares.begin(), pares.end(), make_pair(b, c)) != pares.end() &&
                            find(pares.begin(), pares.end(), make_pair(a, c)) == pares.end()) {
                            transitiva = false;
                        }
                    }
                }
            }
        }

        // Verificar equivalencia
        if (reflexiva && simetrica && transitiva) {
            for (auto a : A) {
                for (auto b : A) {
                    if (find(pares.begin(), pares.end(), make_pair(a, b)) != pares.end() &&
                        find(pares.begin(), pares.end(), make_pair(b, a)) != pares.end()) {
                        for (auto c : A) {
                            if (a != c && b != c) {
                                if (find(pares.begin(), pares.end(), make_pair(a, c)) != pares.end() &&
                                    find(pares.begin(), pares.end(), make_pair(b, c)) != pares.end() &&
                                    find(pares.begin(), pares.end(), make_pair(c, a)) != pares.end() &&
                                    find(pares.begin(), pares.end(), make_pair(c, b)) != pares.end()) {
                                    continue;
                                }
                                else {
                                    equivalencia = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            equivalencia = false;
            orden_parcial = false;
        }

        // Verificar orden parcial
        if (reflexiva && antisimetrica && transitiva) {
            orden_parcial = true;
        }
        else {
            orden_parcial = false;
        }

        cout << "Reflexiva: " << (reflexiva ? "Si" : "No") << endl;
        cout << "Irreflexiva: " << (irreflexiva ? "Si" : "No") << endl;
        cout << "Simetrica: " << (simetrica ? "Si" : "No") << endl;
        cout << "Asimetrica: " << (asimetrica ? "Si" : "No") << endl;
        cout << "Antisimetrica: " << (antisimetrica ? "Si" : "No") << endl;
        cout << "Transitiva: " << (transitiva ? "Si" : "No") << endl;
        cout << "Equivalencia: " << (equivalencia ? "Si" : "No") << endl;
        cout << "Orden parcial: " << (orden_parcial ? "Si" : "No") << endl;
    }

    void producto_cartesiano()
    {
        int n;
        cout << "Ingrese el tamano del conjunto A (entre 4 y 7): ";
        cin >> n;

        if (n < 4 || n > 7)
        {
            cout << "El tamano del conjunto A debe estar entre 4 y 7." << endl;
        }
        else
        {
            vector<string> A(n);

            char opcion;
            cout << "¿Desea generar los elementos de A aleatoriamente (A) o introducirlos manualmente (M)? ";
            cin >> opcion;

            if (opcion == 'A' || opcion == 'a')
            {
                srand(time(NULL));
                for (int i = 0; i < n; i++)
                {
                    int tipo = rand() % 2;
                    if (tipo == 0)
                    {
                        char letra = rand() % 26 + 65;
                        A[i] = letra;
                    }
                    else
                    {
                        int numero = rand() % 8 + 1;
                        A[i] = to_string(numero);
                    }
                }
            }
            else if (opcion == 'M' || opcion == 'm')
            {
                for (int i = 0; i < n; i++)
                {
                    char elemento;
                    bool es_letra = false;
                    while (!es_letra) {
                        cout << "Ingrese el elemento " << i + 1 << " de A: ";
                        cin >> elemento;
                        es_letra = (elemento >= 'A' && elemento <= 'Z') || (elemento >= 'a' && elemento <= 'z') || isdigit(elemento);
                        if (!es_letra)
                        {
                            cout << "El elemento debe ser una letra o un numero. Intentelo de nuevo." << endl;
                        }
                    }
                    A[i] = elemento;
                }
            }
            else
            {
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }

            cout << "El producto cartesiano AxA es:" << endl;
            cout << "{";
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << "(" << A[i] << ", " << A[j] << ")";
                    if (i == n - 1 && j == n - 1)
                    {
                        cout << "}" << endl;
                    }
                    else
                    {
                        cout << ", ";

                    }
                }
            }

            cout << "Desea elegir pares ordenados aleatorios (A) o introducirlos manualmente (M)? ";
            char respuesta;
            cin >> respuesta;

            if (respuesta == 'A' || respuesta == 'a')
            {
                int num_pares;
                cout << "Cuantos pares aleatorios quieres elegir? ";
                cin >> num_pares;

                if (num_pares > n * n)
                {
                    cout << "El numero de pares seleccionados no puede ser mayor que " << n * n << endl;
                }
                else
                {
                    auto pares = elegir_pares_aleatorios(A, num_pares);
                    cout << "Los pares ordenados aleatorios seleccionados son:" << endl;
                    for (auto p : pares)
                    {
                        cout << "(" << p.first << ", " << p.second << ")" << endl;
                    }
                    
                    verificar_propiedades(pares, A);

                }
            }
            else if (respuesta == 'M' || respuesta == 'm')
            {
                int num_pares;
                cout << "Cuantos pares ordenados quieres ingresar? ";
                cin >> num_pares;

                vector<pair<string, string>> pares;

                for (int i = 0; i < num_pares; i++)
                {
                    string elemento1, elemento2;
                    bool es_valido = false;
                    while (!es_valido) {
                        cout << "Ingrese el elemento 1 del par " << i + 1 << ": ";
                        cin >> elemento1;
                        cout << "Ingrese el elemento 2 del par " << i + 1 << ": ";
                        cin >> elemento2;

                        // Verificación de que los elementos del par pertenecen a A
                        if (find(A.begin(), A.end(), elemento1) != A.end() && find(A.begin(), A.end(), elemento2) != A.end())
                        {
                            es_valido = true;
                            pares.push_back(make_pair(elemento1, elemento2));
                        }
                        else
                        {
                            cout << "El par ingresado no es un subconjunto de AxA. Intentelo de nuevo." << endl;
                        }
                    }
                }
                cout << "Los pares ordenados ingresados son: ";
                for (auto par : pares)
                {
                    cout << "(" << par.first << ", " << par.second << ") ";
                }
                cout << endl;

                verificar_propiedades(pares, A);
            }
            else
            {
                cout << "Opcion invalida. Intente de nuevo." << endl;
            }
        }
    }
