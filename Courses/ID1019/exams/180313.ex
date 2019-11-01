defmodule Ten180312 do

  def test_tree() do
    {:tree, 1, {:tree, 0, nil, nil}, {:tree, 2, nil, {:tree, 3, nil, nil}}}
  end

  def summ(nil) do 0 end
  def summ({:tree, val, l, r}) do
    val + summ(l) + summ(r)
  end

  def rev(l) do rev(l, []) end
  def rev([], acc) do acc end
  def rev([h|t], acc) do
    rev(t, [h|acc])
  end 

  def app(a,b) do
    rev(rev(a), b)
  end

  @type heap() :: nil | {:heap, integer(), heap(), heap()}
  @spec new() :: heap()
  @spec add(heap(), integer()) :: heap()
  @spec pop(heap()) :: nil | {:ok, integer(), heap()} 

  def new() do
    nil
  end

  def add(nil, v) do {:heap, v, nil, nil} end
  def add({:heap, val, left, right}, v) when val > v do
    {:heap, val, add(right, v), left}
  end 
  def add({:heap, val, left, right}, v) do
    {:heap, v, add(right, val), left}
  end

  def pop(nil) do :fail end
  def pop({:heap, val, left, nil}) do
    {:ok, val, left}
  end 
  def pop({:heap, val, nil, right}) do
    {:ok, val, right}
  end
  def pop({:heap, val, left, right}) do
    {:heap, l, _, _} = left
    {:heap, r, _, _} = right
    if(l < r) do
      {:ok, _, rest} = pop(right)  
      IO.inspect(rest, width: 40)
      {:ok, val, {:heap, r, left, rest}}
    else
      {:ok, _, rest} = pop(left)
      IO.inspect(rest, width: 40)
      {:ok, val, {:heap, l, rest, right}}
    end
  end

  def swap(nil, v) do
    {:ok, v, nil}
  end
  def swap({:heap, val, left, right}, v) when val > v do
    {:ok, v, left} = swap(left, v)
    IO.write('left ')
    IO.inspect(left)
    IO.write('v ')
    IO.inspect(v)
    IO.write('val ')
    IO.inspect(val)
    {:ok, v, right} = swap(right, v)
    IO.write('right ')
    IO.inspect(right)
    IO.write('v ')
    IO.inspect(v)
    IO.write('val ')
    IO.inspect(val)
    {:ok, val, {:heap, v, left, right}}
    
  end
  def swap(heap, v) do
    {:ok, v, heap}
  end

  

end
