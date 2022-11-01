#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>
#include <QString>
#endif // STRUCTS_HPP

struct Basics
{
    QString name;
    std::pair<QString, QString> open_hours[7];
    int transport_cost;
};

struct Label
{
    std::string name;
    int mode; // 0 - contains; 1 - all
    bool selected = false;
};

struct Topping
{
    std::string name;
    int price;
    std::vector<Label> labels;
    bool selected = false;
};

struct Pizza
{
    std::string name;
    int base_price;
    std::vector<Topping> toppings;

    std::vector<Label> labels;
    int full_price;
    Pizza(std::string p_name, int p_base_price, std::vector<Topping> p_toppings) : name(p_name), base_price(p_base_price), toppings(p_toppings), full_price(base_price) // set labels and full price for the pizza
    {
        for (Topping &t: toppings)
        {
            for (Label &t_l: t.labels)
            {
                if (t_l.mode == 0)
                {
                    bool already_found = false;
                    for (Label &l: labels)
                    {
                        if (t_l.name == l.name) { already_found = true; }
                    }
                    if (!already_found) { labels.push_back(t_l); }
                }
                else
                {
                    bool found_other = false;
                    for (size_t i = 0; i < toppings.size(); i++)
                    {
                        if (i < toppings.size())
                        {
                            size_t sizexd = toppings[i].labels.size();
                            if (sizexd == 0) { found_other = true; }
                            else {
                                for (size_t j = 0; j < sizexd; j++)
                                {
                                    if (toppings[i].labels[j].name != t_l.name)
                                    {
                                        found_other = true;
                                        j = toppings[i].labels.size();
                                        i = toppings.size();
                                    }
                                }
                            }
                        }
                    }

                    if (!found_other)
                    {
                        bool already_found = false;
                        for (Label &l: labels)
                        {
                            if (t_l.name == l.name) { already_found = true; }
                        }
                        if (!already_found) { labels.push_back(t_l); }
                    }
                }
            }
            full_price += t.price;
        }
    }
};
