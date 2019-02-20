defmodule Deriv do

  @type literal() :: {:const, number()}
                    | {:const, atom()}
                    | {:var, atom()}

  @type expr() :: {:add, expr(), expr()}
                  | {:mul, expr(), expr()}
                  | {:exp, expr(), literal()}
                  | literal()

  def test() do
    test =
      {:add, {:mul, {:const, 4}, {:mul, {:var, :x}, {:const, 2}}},
       {:add, {:mul, {:const, 3}, {:var, :x}}, {:const, 42}}}

    der = deriv(test, :x)
  end 

  def deriv({:const, _}, _), do: {:const, 0} 
  def deriv({:var, v}, v), do: {:const, 1} 
  def deriv({:var, y}, _), do: {:const, 0} 
  def deriv({:mul, e1, e2}, v), do: {:add, {:mul, deriv(e1, v), e2},{:mul, e1, deriv(e2, v)}} 
  def deriv({:add, e1, e2}, v), do: {:add, deriv(e1, v), deriv(e2, v)}
  def deriv({:exp, e1, {:const, exp}}, v) do {:mul, {:mul, {:exp, e1, {:const, exp - 1}}, {:const, exp}}, deriv(e1, v)} end
end
