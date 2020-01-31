#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include <fstream>
#include <iostream>
#include <list>
#include <vector>

//#define poly_mod 2048

// #define poly_mod 4096
// #define plain_mod_batch 40961

// this one doesnt work properly

#define poly_mod 8192
#define plain_mod_batch 114689

// #define poly_mod 16384
// #define plain_mod_batch 163841

#define EPSILON 1

#include "seal/seal.h"

using namespace std;
using namespace seal;



int main() {
    // Set up encryption parameters
    // read in site_A parms //
    ifstream infile_parms_A;
    infile_parms_A.open("parms_A.txt");
    EncryptionParameters parms(scheme_type::BFV);
    parms.load(infile_parms_A);


    /*
    We create the SEALContext as usual and print the parameters.
    */
    //auto context = SEALContext::Create(parms);
    auto context = SEALContext::Create(parms, false, sec_level_type::none);
    
    /*
    We can verify that batching is indeed enabled by looking at the encryption
    parameter qualifiers created by SEALContext.
    
    auto qualifiers = context->context_data()->qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.using_batching
         << endl;
    */
    auto qualifiers = context->first_context_data()->qualifiers();


    //KeyGenerator keygen(context);
    //auto secret_key = keygen.secret_key();
    KeyGenerator keygen(context);

    ifstream sk_A;
    sk_A.open("sk_A.txt");
    SecretKey s_key;
    s_key.load(context, sk_A);
    
    /*
    We also set up a Decryptor here.
    */
    Decryptor decryptor(context, s_key);

    
    /*
    Batching is done through an instance of the BatchEncoder class so need to
    construct one.
    */
    BatchEncoder batch_encoder(context);

    ifstream in_file_A;
    in_file_A.open("Site_A_number_seqs.txt");
    int num_seqs_A = 0;
    string line;
    while (getline(in_file_A, line)) {
        stringstream seq_num(line);
        seq_num >> num_seqs_A;
    }
    
    line = "";

    ifstream in_file_B;
    in_file_B.open("Site_B_number_seqs.txt");
    int num_seqs_B = 0;
    while (getline(in_file_B, line)) {
        stringstream seq_num(line);
        seq_num >> num_seqs_B;
    }

    ofstream out("HAMMING_A_B.txt");
    for(int i = 0; i < num_seqs_A; i++){
        for(int j = 0; j < num_seqs_B; j++){
            // decode //
            string a_num_str = to_string(i);
            string b_num_str = to_string(j);
            string inham = "Enc_A_" + a_num_str + "_B_" + b_num_str + ".txt";
            string outham = "HAM_A_" + a_num_str + "_B_" + b_num_str + ".txt";
            
            ifstream infile_ham;
            infile_ham.open(inham);

            Ciphertext compared_ham;
            compared_ham.load(context, infile_ham);
            Plaintext plain_result;
            decryptor.decrypt(compared_ham, plain_result);

            vector<uint64_t> result;
            batch_encoder.decode(plain_result, result);
    

            int ans = result[0]/2;
            int len_of_seq = 4;
            int real_ans = ans % len_of_seq;
            
            cout << "Different Between A " << i + 1 << " and " << "B " << j + 1 << " is: " << real_ans << endl;
            cout << endl;

            string s_ans = to_string(real_ans);
            string out_line = "A_" + a_num_str + "_B_" + b_num_str + ":" + s_ans + "\n";  

            out << out_line;
        }
    }
    out.close();
}

