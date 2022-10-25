#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>
#endif // STRUCTS_HPP

struct Label
{
    std::string name;
    int mode : 1; // 0 - contains; 1 - all
};

struct Topping
{
    std::string name;
    int price;
    std::vector<Label> labels;
};

struct Pizza
{
    std::string name;
    int base_price;
    std::vector<Topping> toppings;

    std::vector<Label> labels;
    Pizza(std::string p_name, int p_base_price, std::vector<Topping> p_toppings) : name(p_name), base_price(p_base_price), toppings(p_toppings) // set labels for the pizza
    {
        for (Topping t: toppings)
        {
            for (Label t_l: t.labels)
            {
                if (t_l.mode == 0) { labels.push_back(t_l); }
                else
                {
                    bool found_other = false;
                    for (size_t i = 0; i < toppings.size(); i++)
                    {
                        for (size_t j = 0; j < toppings[i].labels.size(); j++)
                        {
                            if (toppings[i].labels[j].name != t_l.name)
                            {
                                found_other = true;
                                j = toppings[i].labels.size();
                                i = toppings.size();
                            }
                        }
                    }

                    if (!found_other) { labels.push_back(t_l); }
                }
            }
        }
    }
};