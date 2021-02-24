//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    if (m_pHead == NULL) return;
    Element_t *tmp = m_pHead->pNext;
    m_pHead->pNext = NULL;
    while (tmp->pNext != NULL)
    {
        Element_t *hold = tmp->pNext;
        delete(tmp);
        tmp = hold;
    }
    delete(m_pHead);
    m_pHead = NULL;
}

void PriorityQueue::Insert(int value)
{
    if (m_pHead == NULL)
    {
        m_pHead = new Element_t;
        m_pHead->value = value;
        m_pHead->pNext = NULL;
    }
    else
    {
        if (m_pHead->value < value)
        {
            Element_t *newElem = new Element_t;
            newElem->value = m_pHead->value;
            newElem->pNext = m_pHead->pNext;

            m_pHead->pNext = newElem;
            m_pHead->value = value;
        }
        else
        {
            Element_t *tmp = m_pHead;
            while (tmp->value > value)
            {
                if (tmp->pNext == NULL)
                {
                    Element_t *newElem = new Element_t;
                    newElem->pNext = NULL;
                    newElem->value = value;

                    tmp->pNext = newElem;
                    return;
                }
                if (tmp->pNext->value <= value)
                    break;
                tmp = tmp->pNext;
            }

            Element_t *newElem = new Element_t;
            newElem->value = value;
            newElem->pNext = tmp->pNext;
            
            tmp->pNext = newElem;
        }
    }
}



bool PriorityQueue::Remove(int value)
{
    if (m_pHead == NULL)
        return false;

    Element_t *tmp = m_pHead;
    if (tmp->value < value)
        return false;

    if (tmp->value == value)
    {
        m_pHead = tmp->pNext;
        delete(tmp);
        tmp = NULL;
        return true;
    }
    
    while (tmp->value != value)
    {
        if (tmp->pNext == NULL)
            return false;
        if (tmp->pNext->pNext == NULL && tmp->pNext->value == value)
        {
            Element_t *hold = tmp->pNext;
            tmp->pNext = NULL;
            delete(hold);
            hold = NULL;
            return true;
        }
        tmp = tmp->pNext;
    }

    Element_t *hold = tmp;
    m_pHead = NULL;
    delete(hold);
    hold = NULL;
    return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    if (m_pHead == NULL)
        return NULL;

    if (m_pHead->value < value)
        return NULL;

    Element_t *tmp = m_pHead;
    while (tmp->value != value)
    {
        if (tmp->pNext == NULL)
            return NULL;
        tmp = tmp->pNext;
    }
    return tmp;
}

size_t PriorityQueue::Length()
{
    if (m_pHead == NULL)
        return 0;

    int length = 0;
    Element_t *tmp = m_pHead;
    while (tmp != NULL)
    {
        length++;
        tmp = tmp->pNext;
    }
    return length;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    if (m_pHead == NULL)
        return NULL;
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
