# Project CST ADS School

> The code is filled with comments for easy and quick navigation by the team.

## Why choose String for fields like RG and vCods?
Because we follow a simple rule: when we deal with immutable numbers — meaning numbers we won’t perform arithmetic operations on — they don’t need to be stored as numeric types. Instead, they should be treated as defined text. Additionally, there's a risk of losing the leading zero in an RG (Brazilian ID number), as RGs can start with 0, and storing them as integers may lead to rounding or truncation.

## Why use int for monetary values?
Although it might seem unnecessary at first glance, using int is actually one of the best industry practices. float or double types can lead to inconsistencies due to precision errors, which may cause small but impactful financial losses. That’s why we usually use decimal or even int. Yes, int — as long as we know where the decimal point is. This way, we can represent cents without losing precision or facing unnecessary rounding.
Why this choice? Simply due to knowledge and best practices.
