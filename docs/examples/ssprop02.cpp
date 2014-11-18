/*
 * Property template example 2.
 * The class implementation.
 */
ArrayList::ArrayList() : count(this), m_list(NULL)
{
    count.getter<ArrayList>(&ArrayList::get_count);
}

size_t get_count() {
    return (m_list ? m_list->size() : 0);
}

