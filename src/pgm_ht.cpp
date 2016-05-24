/*!
 *  @mainpage  Implementação da tabela e função rehash
 *  @author Johnnylee Bryan Marques da Rocha
 *  @date Maio, 2016
 *  @version 1.0
 *
 *  @file pgm_ht.cpp
 *  @brief Arquivo Main
 *
 *  Arquivo de inicialização do programa
 */

#include <iostream>
#include <functional>
#include <tuple>

#include "hashtbl.h"

using namespace std;

struct Account
{
    std::string mClientName;// (key) Client's name.
    int mBankCode;          // (key) Bank code.
    int mBranchCode;        // (key) Branch code.
    int mNumber;            // (key) Account number.
    float mBalance;         // Account balance.

#ifdef SIMPLE
    using AcctKey = int;
#endif

#ifdef STILLSIMPLE
    using AcctKey = std::pair<std::string, int>;
#endif

#ifdef NOTTHATSIMPLE
    using AcctKey = tuple<string, int, int, int>;
#endif

    Account( std::string _Name = "<empty>",
             int _BankCode = 1,  // Banco do Brasil.
             int _BranchCode = 1668, // Agencia UFRN.
             int _Number = 0,
             float _Balance = 0.f )
        :  mClientName( _Name ),
           mBankCode( _BankCode ),
           mBranchCode( _BranchCode ),
           mNumber( _Number ),
           mBalance( _Balance )
        { /* Empty */ }

    /*!
     * \brief versão 1 que eh igual a conta corrente.
     */
#ifdef SIMPLE
    /*!
     * \brief Gera a chave (versão 1) que eh igual a conta corrente.
     */
    AcctKey getKey () const
    {
        return mNumber;
    }
#endif

#ifdef STILLSIMPLE
    /*!
     * \brief Gera a chave (versão 2) que eh igual ao nome do cliente e o numero da conta.
     */
    AcctKey getKey () const
    {
        return {mClientName, mNumber};
    }
#endif

#ifdef NOTTHATSIMPLE
    /*!
     * \brief Gera a chave (versão 3) com o nome do cliente, codigo do banco, numero da agencia e numero da conta.
     */
    AcctKey getKey () const
    {
        return std::tuple < std::string , int, int, int >(mClientName, mBankCode, mBranchCode, mNumber);
    }

#endif
    const Account& operator= ( const Account& rhs )
    {
        // Avoid assigning to itself.
        if( this != &rhs )
        {
            // Copy new values.
            this->mClientName = rhs.mClientName;
            this->mBankCode   = rhs.mBankCode;
            this->mBranchCode = rhs.mBranchCode;
            this->mNumber     = rhs.mNumber;
            this->mBalance    = rhs.mBalance;
        }
        return *this;
    }

    //TODO friend para imprimir
    inline friend std::ostream &operator<< ( std::ostream& _os, const Account& _acc )
    {
        _os << "[ Client: <"  << _acc.mClientName <<
               "> Bank: <"    << _acc.mBankCode <<
               "> Branch: <"  << _acc.mBranchCode <<
               "> Number: <"  << _acc.mNumber <<
               "> Balance: <" << _acc.mBalance << "> ]";
        return _os;
    }
};

#ifdef SIMPLE
struct KeyHash {
    std::size_t operator()(const Account::AcctKey& k) const {

        return std::hash<int>()(k);
    }
};

struct KeyEqual {
    bool operator()(const Account::AcctKey &lhs, const Account::AcctKey &rhs) const {
        return lhs == rhs;
    }
};

#endif

#ifdef STILLSIMPLE

struct KeyHash {
    std::size_t operator()(const Account::AcctKey& k) const
    {
        return (std::hash<std::string>()(k.first) xor std::hash<int>()(k.second));
    }
};

struct KeyEqual {
    bool operator()(const Account::AcctKey& lhs, const Account::AcctKey& rhs) const
    {
        return lhs.first == rhs.first and lhs.second == rhs.second;
    }
};

#endif

#ifdef NOTTHATSIMPLE


struct KeyHash {
    std::size_t operator()(const Account::AcctKey& k) const {
        return hash<string>()(get<0>(k)) xor
               hash<int>()(get<1>(k)) xor
               hash<int>()(get<2>(k)) xor
               hash<int>()(get<3>(k));
    }
};

struct KeyEqual {
    bool operator()(const Account::AcctKey& lhs, const Account::AcctKey& rhs) const {
        return get<0>(lhs) == get<0>(rhs) and
               get<1>(lhs) == get<1>(rhs) and
               get<2>(lhs) == get<2>(rhs) and
               get<3>(lhs) == get<3>(rhs);
    }
};
#endif



int main( void )
{
    MyHashTable::HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > accounts(23); // Hash table shall heve size 23.
    Account MyAccts[] =
    {
        { "Jose Silva",    1, 1668, 20123, 1500.f },
        { "Carlos Prado",  1, 1668, 35091, 1250.f },
        { "Aline Bastos", 13,   33, 55723,  500.f },
        { "Pedro Gomes",   1, 1801, 87661, 5800.f },
    };

    auto nAccts = sizeof( MyAccts ) / sizeof( Account );

    for ( auto i(0u) ; i < nAccts ; ++i )
    {
        accounts.insert( MyAccts[i].getKey() , MyAccts[i] );
    }

    accounts.showStructure();
#ifdef SIMPLE

    Account::AcctKey searchKey;
    Account acct;
    // Checks for accounts and prints records if found
    cout << endl;
    cout << "Enter account number (CTRL+D to exit program): ";
    while ( cin >> searchKey )
    {

        if ( accounts.retrieve( searchKey, acct ) )
        {
            cout << acct.mNumber << " " << acct.mBalance << endl;
            cout << "Removing this account....\n";
            accounts.remove( acct.getKey() );
        }
        else
            cout << "Account " << searchKey << " not found." << endl;

        accounts.showStructure();
        cout << "Enter account number (CTRL+D to exit program): ";
    }
        accounts.clear();

#endif

#ifdef STILLSIMPLE

    Account::AcctKey searchKey;
    Account acct;
    cout << endl;
    cout << "Enter account name (CTRL+D to exit program): ";
    while (getline(cin, searchKey.first))
    {
        cout << "Enter account number: ";
        cin >> searchKey.second;
        if (accounts.retrieve( searchKey, acct ))
        {
            cout << acct.mClientName << " " << acct.mNumber << " " << acct.mBalance << endl;
            cout << "Removing this account....\n";
            accounts.remove(acct.getKey());
        }
        else
            cout << "Account " << searchKey.first << " " << searchKey.second << " not found." << endl;

        accounts.showStructure();
        cout << "Enter account number (CTRL+D to exit program): ";
    }

#endif

#ifdef NOTTHATSIMPLE
    Account::AcctKey searchKey;
    Account acct;
    cout << endl;
    cout << "Enter account name (CTRL+D to exit program): ";
    while (getline(cin, get<0>(searchKey)))
    {
        cout << "Enter bank code: ";
        cin >> get<1>(searchKey);
        cout << "Enter branch code: ";
        cin >> get<2>(searchKey);
        cout << "Enter account number: ";
        cin >> get<3>(searchKey);
        if (accounts.retrieve( searchKey, acct ))
        {
            cout << acct.mClientName << " " <<  acct.mNumber << " " << acct.mBalance  << " " << acct.mBankCode << " " << acct.mBranchCode  << endl;
            cout << "Removing this account....\n";
            accounts.remove( acct.getKey() );
        }
        else
            cout << "Account " << get<0>(searchKey) << " " << get<1>(searchKey) << get<2>(searchKey) << get<3>(searchKey) << " not found." << endl;

        accounts.showStructure();
        cout << "Enter account number (CTRL+D to exit program): ";
    }
#endif

    std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}
