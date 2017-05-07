using namespace std;

template<class E>

class Vertex
{
	private:
		E element;
		int index;

		bool wasVisited;
		//List of edges (if Edge class not used).
	public:
		Vertex(E data, int position);
		~Vertex();
};

template<class E>
Vertex<E>::Vertex(E data, int position)
{
	element = data;
	index = position;

	wasVisited = false;
}

template<class E>
Vertex<E>::~Vertex()
{
	//Delete vertex.
}