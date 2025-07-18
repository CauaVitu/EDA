/**
 * @file OpenHash.hpp
 * @author your name
 * @brief Tabela hash com enderecamento aberto (linear probing).
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-04
 * 
 * @copyright Copyright (c) 2025
 */
#ifndef OPEN_HASH_HPP
#define OPEN_HASH_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <optional>

/**
 * @brief Classe que implementa uma tabela hash com enderecamento aberto (linear probing).
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenHash {
private:
    enum class EntryState { EMPTY, OCCUPIED, DELETED };

    struct Entry {
        Key key;
        Value value;
        EntryState state = EntryState::EMPTY;

        Entry() = default;
        Entry(const Key& k, const Value& v) : key(k), value(v), state(EntryState::OCCUPIED) {}
    };

    std::vector<Entry> m_table;
    size_t m_size = 0;
    float m_max_load_factor;
    Hash m_hash;
    mutable int comparison_counter = 0;
    mutable int colision_counter = 0;

    size_t get_next_prime(size_t x) const {
        if (x <= 2) return 3;
        x = (x % 2 == 0) ? x + 1 : x;
        while (true) {
            bool is_prime = true;
            for (size_t i = 3; i <= std::sqrt(x); i += 2) {
                if (x % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) return x;
            x += 2;
        }
    }

    // Optei por usar linear probing para resolver colisões
    size_t probe(const Key& key, bool for_insert = false) const {
        size_t index = m_hash(key) % m_table.size();
        size_t start = index;
        do {
            comparison_counter++;
            if (m_table[index].state == EntryState::EMPTY) return index;
            if (m_table[index].state == EntryState::OCCUPIED && m_table[index].key == key) return index;
            else colision_counter++; 
            index = (index + 1) % m_table.size();
        } while (index != start);
        throw std::overflow_error("Hash table is full");


    }

    void rehash(size_t new_size) {
        new_size = get_next_prime(new_size);
        std::vector<Entry> old_table = m_table;
        m_table = std::vector<Entry>(new_size);
        m_size = 0;
        for (const auto& entry : old_table) {
            if (entry.state == EntryState::OCCUPIED) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    OpenHash(size_t tableSize = 19, float load_factor = 0.7f) {
        tableSize = get_next_prime(tableSize);
        m_table.resize(tableSize);
        m_max_load_factor = (load_factor <= 0) ? 0.7f : load_factor;
    }

    // Itera sobre os elementos da tabela hash e retorna um vetor de pares (key, value)
    std::vector<std::pair<Key,Value>> iterate (){
        std::vector<std::pair<Key, Value>> result;
        for (const auto& entry : m_table) {
            if (entry.state == EntryState::OCCUPIED) {
                result.emplace_back(entry.key, entry.value);
            }
        }
        return result;
    }

    // Insere um novo elemento no slot apropriado da tabela hash.
    // Se chegarmos no load_factor rehash é chamado para aumentar o tamanho da tabela.
    bool insert(const Key& key, const Value& value) {
        if (static_cast<float>(m_size + 1) / m_table.size() > m_max_load_factor) {
            rehash(m_table.size() * 2);
        }
        size_t index = probe(key);
        if (m_table[index].state == EntryState::OCCUPIED && m_table[index].key == key) return false;
        m_table[index] = Entry(key, value);
        m_size++;
        return true;
    }

    // Remove um elemento da tabela hash, marcando-o como DELETED.
    bool remove(const Key& key) {
        size_t index = probe(key);
        if (m_table[index].state == EntryState::OCCUPIED && m_table[index].key == key) {
            m_table[index].state = EntryState::DELETED;
            m_size--;
            return true;
        }
        return false;
    }

    // Verifica se um elemento está presente na tabela hash.
    // Retorna true se o elemento estiver presente, false caso contrário.
    bool contains(const Key& key) const {
        size_t index = probe(key);
        return m_table[index].state == EntryState::OCCUPIED && m_table[index].key == key;
    }

    // Retorna o valor associado a uma chave, se existir.
    Value& at(const Key& key) {
        size_t index = probe(key);
        if (m_table[index].state == EntryState::OCCUPIED) {
            return m_table[index].value;
        }
        throw std::out_of_range("Key not found");
    }

    int get_comparison_counter() const {
        return comparison_counter;
    }
    int get_colision_counter() const {
        return colision_counter;
    }

    // Parece uma duplicada, mas esse cara aqui é const e o outro não
    const Value& at(const Key& key) const {
        size_t index = probe(key);
        if (m_table[index].state == EntryState::OCCUPIED) {
            return m_table[index].value;
        }
        throw std::out_of_range("Key not found");
    }

    Value& operator[](const Key& key) {
        size_t index = probe(key);
        if (m_table[index].state == EntryState::OCCUPIED) {
            return m_table[index].value;
        }
        m_table[index] = Entry(key, Value());
        m_size++;
        return m_table[index].value;
    }

    // Limpa a tabela hash, removendo todos os elementos.
    // Redimensiona a tabela para o tamanho inicial.
    void clear() {
        m_table.clear();
        m_table.resize(get_next_prime(19));
        m_size = 0;
    }

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    float load_factor() const { return static_cast<float>(m_size) / m_table.size(); }
    float max_load_factor() const { return m_max_load_factor; }
    void set_max_load_factor(float lf) {
        if (lf <= 0) throw std::out_of_range("Invalid load factor");
        m_max_load_factor = lf;
        if (load_factor() > m_max_load_factor) {
            rehash(m_table.size() * 2);
        }
    }
};

#endif // OPEN_ADDRESS_HASHTABLE_HPP
