#include"core.h"
namespace core{
	class tool{
	public:
		tool() = default;
		void wait(int mili_s){
			std::this_thread::sleep_for(std::chrono::milliseconds(mili_s));
		}
		void clear(){system("CLS");}
		class vec2{
		public:
			vec2() = default;
			vec2(int x, int y):m_x(x),m_y(y){}
			vec2(float x,float y):m_x(static_cast<int>(x)),m_y(static_cast<int>(y)){}
			vec2(double x,double y):m_x(static_cast<int>(x)),m_y(static_cast<int>(y)){}
			int getX() { return m_x; }
			int getY() { return m_y; }
			COORD toCord(){
				return COORD { static_cast<short>(m_x),static_cast<short>(m_y) };}
		private:
			int m_x, m_y;
		};
		class vec3{
		public:
			vec3() = default;
			vec3(int x, int y,int z):m_x(x),m_y(y),m_z(z){}
			vec3(float x,float y,float z):m_x(static_cast<int>(x)),m_y(static_cast<int>(y)),m_z(static_cast<int>(z)){}		
			vec3(double x,double y,double z):m_x(static_cast<int>(x)),m_y(static_cast<int>(y)),m_z(static_cast<int>(z)){}
			int getX() { return m_x; }
			int getY() { return m_y; }
			int getZ() { return m_z; }
		private:
			int m_x, m_y,m_z;
		};
		void gotoxy(vec2 pos){
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos.toCord());
		}
		void gotoxy(int x, int y){
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),vec2(x,y).toCord());
		}
	};
	class Screen {
	public:
		Screen() = default;
		double width = 120;
		double height = 120;
		static constexpr const char* winName = " ";
	};
	class render: public Screen, public tool {
	public:
		render() = default;
		Screen screen;
		tool tl;
	};
	class draw: public render{
	public:
		draw() = default;
		void Xline(vec2 startPos,int width) {
			auto _line = []() { std::cout << "#"; };
			int xrend = startPos.getX();
			int yrend = startPos.getY();
			int x = width;
			for (xrend;xrend<x;++xrend){
				tl.gotoxy(xrend, yrend);
				_line();
			}
		}
		void Yline(vec2 startPos,int height) {
			auto _line = []() { std::cout << "#"; };
			int xrend = startPos.getX();
			int yrend = startPos.getY();
			int y = height;
			for (yrend;yrend<y;++yrend){
				tl.gotoxy(xrend,yrend);
				_line();
				tl.gotoxy(xrend,yrend+1);
				_line();
			}
		}
		void square(vec2 StartPos,vec2 _size) {
			tl.clear();
			vec2 size = vec2(_size.getX()-1, _size.getY()-1);
			Xline(StartPos, size.getX());
			Yline(StartPos, size.getY());
			Yline(vec2(size.getX(), StartPos.getY()),size.getY());
			Xline(vec2(StartPos.getX(), size.getX()), size.getX());
		}
		void cube(vec2 StartPos,vec3 _size){
			//TODO:do it!
		}
	private:
		void DiagonalLineUp(vec2 startPos, int length) {
			auto _line = []() { std::cout << "#"; };
			int xrend = startPos.getX();
			int yrend = startPos.getY();
			tl.clear();
			for (int i = 0; i < length; ++i) {
				gotoxy(xrend - i, yrend + i);
				_line();
			}
		}

		void DiagonalLineDown(vec2 startPos, int length) {
			auto _line = []() { std::cout << "#"; };
			int xrend = startPos.getX();
			int yrend = startPos.getY();
			tl.clear();
			for (int i = 0; i < length; ++i) {
				tl.gotoxy(xrend + i, yrend - i);
				_line();
			}
		}

		void DiagonalLineLeft(vec2 startPos, int length) {
			auto _line = []() { std::cout << "#"; };
			int xrend = startPos.getX();
			int yrend = startPos.getY();
			tl.clear();
			for (int i = 0; i < length; ++i) {
				gotoxy(xrend - i, yrend - i);
				_line();
			}
		}

		void DiagonalLineRight(vec2 startPos, int length) {
			auto _line = []() { std::cout << "#"; };
			int xrend = startPos.getX();
			int yrend = startPos.getY();
			tl.clear();
			for (int i = 0; i < length; ++i) {
				tl.gotoxy(xrend + i, yrend + i);
				_line();
			}
		}
	};
}
namespace utilities{
	// continue is a set of templates for some function
	class TGame {
	public:
		TGame() = default;
		virtual void Update() = 0;
		virtual void mainloop(std::function<void()> func) = 0;
		char getch(char& ch) {
			ch = getchar();
			return ch;
		}
			core::draw draw;
			core::tool tl;
			bool RunTime = true;
	};
}