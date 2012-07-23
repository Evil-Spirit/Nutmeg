//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// url:			http://nutmeg-engine.ru
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#ifndef FunctionH
#define FunctionH

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// Functor definition
	// here is some especial template-macros magic :)
	//
	//--------------------------------------------------------------------------

	#define DEFINE_FUNCTOR(N) 																							\
																														\
	template <typename Result TEMP_DEF_PARAM(N)>																		\
																														\
	class FunctorAbstract##N {																							\
																														\
	public:																												\
																														\
		virtual ~FunctorAbstract##N() { }																				\
																														\
		virtual Result invoke(FUNC_DEF_PARAM(N)) const = 0;																\
		virtual FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> *clone() const = 0;										\
																														\
	};																													\
																														\
	template <typename Result TEMP_DEF_PARAM(N)>																		\
	class FunctionImpl##N : public FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> {										\
																														\
	public:																												\
																														\
		typedef Result (*Type)(FUNC_PTR_PARAM(N));																		\
																														\
		FunctionImpl##N(Type f) {																						\
			func = f;																									\
			assert(func != NULL);																						\
		}																												\
																														\
		virtual Result invoke(FUNC_DEF_PARAM(N)) const {																\
			return func(FUNC_INV_PARAM(N));																				\
		}																												\
																														\
		virtual FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> *clone() const {											\
			return new FunctionImpl##N <Result TEMP_SPC_PARAM(N)> (func);												\
		}																												\
																														\
	private:																											\
																														\
		Type func;																										\
																														\
	};																													\
																														\
	template <typename Instance, typename Result TEMP_DEF_PARAM(N)>														\
	class MemberImpl##N : public FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> {										\
																														\
	public:																												\
																														\
		typedef Result (Instance::*Type)(FUNC_PTR_PARAM(N));															\
																														\
		MemberImpl##N(Type f, Instance *inst) {																			\
			member = f;																									\
			assert(member != NULL);																						\
			instance = inst;																							\
			assert(instance != NULL);																					\
		}																												\
																														\
		virtual Result invoke(FUNC_DEF_PARAM(N)) const {																\
			return (instance->*member)(FUNC_INV_PARAM(N));																\
		}																												\
																														\
		virtual FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> *clone() const {											\
			return new MemberImpl##N <Instance, Result TEMP_SPC_PARAM(N)> (member, instance);							\
		}																												\
																														\
	private:																											\
																														\
		Type member;																									\
		Instance *instance;																								\
																														\
	};																													\
																														\
	template <typename Result TEMP_DEF_PARAM(N)>																		\
	class Functor##N {																									\
																														\
		const FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> *functor_ptr;												\
																														\
		void clear() {																									\
			delete functor_ptr;																							\
			functor_ptr = NULL;																							\
		}																												\
																														\
	public:																												\
																														\
		Functor##N(typename FunctionImpl##N <Result TEMP_SPC_PARAM(N)> :: Type func) {									\
			functor_ptr = new FunctionImpl##N <Result TEMP_SPC_PARAM(N)> (func);										\
		}																												\
																														\
		template <typename Instance>																					\
		Functor##N(typename MemberImpl##N <Instance, Result TEMP_SPC_PARAM(N)> :: Type member, Instance *instance) {	\
			functor_ptr = new MemberImpl##N <Instance, Result TEMP_SPC_PARAM(N)> (member, instance);					\
		}																												\
																														\
		Functor##N(FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> *ptr = NULL) {											\
			functor_ptr = ptr;																							\
		}																												\
																														\
		Functor##N(const Functor##N <Result TEMP_SPC_PARAM(N)> &o) : functor_ptr(NULL) {								\
			*this = o;																									\
		}																												\
																														\
		~Functor##N() {																									\
			clear();																									\
		}																												\
																														\
		Result operator() (FUNC_DEF_PARAM(N)) const {																	\
			if (functor_ptr == NULL) return Result();																	\
			return functor_ptr->invoke(FUNC_INV_PARAM(N));																\
		}																												\
																														\
		Result invoke(FUNC_DEF_PARAM(N)) const {																		\
			if (functor_ptr == NULL) return Result();																	\
			return functor_ptr->invoke(FUNC_INV_PARAM(N));																\
		}																												\
																														\
		Functor##N <Result TEMP_SPC_PARAM(N)> &operator= (const Functor##N <Result TEMP_SPC_PARAM(N)> &o) {				\
			clear();																									\
			if (o.functor_ptr == NULL) return *this;																	\
			functor_ptr = o.functor_ptr->clone();																		\
			return *this;																								\
		}																												\
																														\
		void set(const FunctorAbstract##N <Result TEMP_SPC_PARAM(N)> *o) {												\
			clear();																									\
			if (o == NULL) return;																						\
			functor_ptr = o;																							\
		}																												\
																														\
	};																													\
																														\
	template <typename Result TEMP_DEF_PARAM(N)> 																		\
	Functor##N <Result TEMP_SPC_PARAM(N)> createFunctor(Result (*func)(FUNC_PTR_PARAM(N))) { 							\
		return Functor##N <Result TEMP_SPC_PARAM(N)> (func);															\
	}																													\
																														\
	template <typename Instance, typename Result TEMP_DEF_PARAM(N)> 													\
	Functor##N <Result TEMP_SPC_PARAM(N)> createFunctor(																\
		Result (Instance::*func)(FUNC_PTR_PARAM(N)), Instance *instance) 												\
	{ 																													\
		return Functor##N <Result TEMP_SPC_PARAM(N)> (func, instance);													\
	}

	//--------------------------------------------------------------------------

	#define DEF_P(X, Y, N) X##N
	#define DEF_D(X, Y, N) X##N Y##N
	#define DP1(DT, X, Y) DT(X, Y, 0)

	//--------------------------------------------------------------------------

	#define DP2(DT, X, Y) DP1(DT, X, Y), DT(X, Y, 1)
	#define DP3(DT, X, Y) DP2(DT, X, Y), DT(X, Y, 2)
	#define DP4(DT, X, Y) DP3(DT, X, Y), DT(X, Y, 3)
	#define DP5(DT, X, Y) DP4(DT, X, Y), DT(X, Y, 4)
	#define DP6(DT, X, Y) DP5(DT, X, Y), DT(X, Y, 5)
	#define DP7(DT, X, Y) DP6(DT, X, Y), DT(X, Y, 6)
	#define DP8(DT, X, Y) DP7(DT, X, Y), DT(X, Y, 7)
	#define DP9(DT, X, Y) DP8(DT, X, Y), DT(X, Y, 8)
	#define DP10(DT, X, Y) DP9(DT, X, Y), DT(X, Y, 9)
	#define DP11(DT, X, Y) DP10(DT, X, Y), DT(X, Y, 10)
	#define DP12(DT, X, Y) DP11(DT, X, Y), DT(X, Y, 11)
	#define DP13(DT, X, Y) DP12(DT, X, Y), DT(X, Y, 12)
	#define DP14(DT, X, Y) DP13(DT, X, Y), DT(X, Y, 13)
	#define DP15(DT, X, Y) DP14(DT, X, Y), DT(X, Y, 14)

	//--------------------------------------------------------------------------
	// define functor for params count 0
	//--------------------------------------------------------------------------

	#define TEMP_DEF_PARAM(N)
	#define TEMP_SPC_PARAM(N)
	#define FUNC_PTR_PARAM(N)
	#define FUNC_INV_PARAM(N)
	#define FUNC_DEF_PARAM(N)
	DEFINE_FUNCTOR(0);

	#undef TEMP_DEF_PARAM
	#undef TEMP_SPC_PARAM
	#undef FUNC_PTR_PARAM
	#undef FUNC_INV_PARAM
	#undef FUNC_DEF_PARAM

	//--------------------------------------------------------------------------
	// define functor for other params counts
	//--------------------------------------------------------------------------

	#define TEMP_DEF_PARAM(N) 	,DP##N(DEF_P, typename T,)
	#define TEMP_SPC_PARAM(N)	,DP##N(DEF_P, T,)
	#define FUNC_PTR_PARAM(N)	DP##N(DEF_P, T,)
	#define FUNC_INV_PARAM(N)	DP##N(DEF_P, p,)
	#define FUNC_DEF_PARAM(N)	DP##N(DEF_D, T, p)

	DEFINE_FUNCTOR(1);
	DEFINE_FUNCTOR(2);
	DEFINE_FUNCTOR(3);
	DEFINE_FUNCTOR(4);
	DEFINE_FUNCTOR(5);
	DEFINE_FUNCTOR(6);
	DEFINE_FUNCTOR(7);
	DEFINE_FUNCTOR(8);
	DEFINE_FUNCTOR(9);
	DEFINE_FUNCTOR(10);
	DEFINE_FUNCTOR(11);
	DEFINE_FUNCTOR(12);
	DEFINE_FUNCTOR(13);
	DEFINE_FUNCTOR(14);
	DEFINE_FUNCTOR(15);

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
