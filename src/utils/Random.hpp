#ifndef GOL_RANDOM_HPP
#define GOL_RANDOM_HPP

namespace gol
{

	class Random
	{
	private:
		static bool initialized_;

		static void init();
		Random() { }
        ~Random() { }
	public:


		static int nextInt();
		static int nextInt(const int p_range);

		static float nextFloat();

		static bool nextBool();

	};

}

#endif
