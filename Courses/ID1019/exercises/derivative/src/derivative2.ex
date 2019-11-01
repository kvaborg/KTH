defmodule Deriv2 do

  @type literal() :: {:const, number()} 
                  | {:const, atom()}
                  | {:var, atom()}
  
  @type expr() :: {:add, expr(), expr()}
              | {:mul, expr(), expr()}
              | literal() 

  def test_expr() do 
    {:add, {:mul, {:const, 2}, {:var, :x}}, {:const, 5}}
  end 


  def deriv({:const, _}, _) do {:const, 0} end
  def deriv({:var, v}, v) do {:const, 1}  end
  def deriv({:var, y}, _) do {:const, 0} end
  def deriv({:mul, e1, e2}, v) do {:add, {:mul, deriv(e1, v), e2}, {:mul, deriv(e2, v), e1}} end
  def deriv({:add, e1, e2}, v) do {:add, deriv(e1, v), deriv(e2, v)} end

end
