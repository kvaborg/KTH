defmodule Test2019 do

  @type tree :: {:node, integer(), tree(), tree()} | nil

  def test_tree() do
    {:node, 1, {:node, 2, {:node, 4, {:node, 7, nil, nil}, nil}, {:node, 5, nil, nil}}, {:node, 3, {:node, 6, nil, nil}, nil}}
  end

  def dbl_even_tail(list) do dbl_even_tail(list, []) end
  def dbl_even_tail([], done) do done end
  def dbl_even_tail([h | t], acc) do
    case rem(h, 2) do
      0 -> dbl_even_tail(t,  acc ++ [h*2])
      _ -> dbl_even_tail(t, acc ++ [h])
    end
  end

  def dbl_even([]) do [] end
  def dbl_even([h|t]) when rem(h,2) == 0 do
    [h*2 | dbl_even(t)]
  end  
  def dbl_even([h|t]) do
    [h | dbl_even(t)]
  end  

  def sum(nil) do 0 end
  def sum({:node, val, left, right}) do
    val + sum(left) + sum(right)
  end 

  # def mirror({:node, val, nil, nil}) do {:node, val, nil, nil} end
  # def mirror({:node, val, nil, right}) do {:node, val, mirror(right), nil} end
  # def mirror({:node, val, left, nil}) do {:node, val, nil, mirror(left)} end
  # def mirror({:node, val, left, right}) do {:node, val, mirror(right), mirror(left)} end
  # 
  
  def mirror(nil) do nil end
  def mirror({:node, val, left, right}) do
    {:node, val, mirror(right), mirror(left)}
  end

  @type heap :: {:heap, any(), heap(), heap()} | nil
  @spec new() :: heap()
  @spec add(heap(), integer()) :: heap()

    
  def new() do
    nil
  end

  def add(nil, val) do {:heap, val, nil, nil} end
  def add({:heap, val, left, right}, k) when k < val do
    {:heap, k, add(right, val), left}
  end
  def add({:heap, val, left, right}, k) do
    {:heap, val, add(right, k), left}
  end
  



  def fizzbuzz(n) do fizzbuzz(1, n+1, 1, 1) end

  def fizzbuzz(max, max, _, _) do [] end
  def fizzbuzz(next, max, 3, 5) do [:fizzbuzz | fizzbuzz(next+1, max, 1, 1)] end
  def fizzbuzz(next, max, 3, c2) do [:fizz | fizzbuzz(next+1, max, 1, c2+1)] end
  def fizzbuzz(next, max, c1, 5) do [:buzz |fizzbuzz(next+1, max, c1+1, 1)] end
  def fizzbuzz(next, max, c1, c2) do [next | fizzbuzz(next+1, max, c1+1, c2+1)] end

end
