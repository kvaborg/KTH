defmodule Tenta20180313 do

  def reverse(list) do 
    reverse(list, [])
  end

  def reverse([], done) do done end
  def reverse([h|t], acc) do
    reverse(t, [h|acc])
  end

  def apnd(list, elem) do
    reverse(reverse(list), elem)
  end

  def test_tree() do
    {:node, {:leaf, 5}, nil}
  end

  @type heap :: nil | {:heap, integer(), heap(), heap()}
  @spec new :: heap()

  def new() do
    nil
  end

  def add(nil, v) do
    {:heap, v, nil, nil}
  end
  def add({:heap, k, left, right}, v) when k > v do
    {:heap, k, add(right, v), left}
  end
  def add({:heap, k, left, right}, v) do
    {:heap, v, add(right, k), left}
  end  

  @spec pop(heap()) :: :fail | {:ok, integer(), heap()}

  def pop(nil) do :fail end
  def pop({:heap, k, left, nil}) do {:ok, k, left} end
  def pop({:heap, k, nil, right}) do {:ok, k, right} end
  def pop({:heap, k, left, right}) do
    {:heap, vl, _, _} = left
    {:heap, vr, _, _} = right
    if vl < vr do
      {:ok, _, rest} = pop(right)
      {:ok, k, {:heap, vr, left, rest}}
    else
      {:ok, _, rest} = pop(left)
      {:ok, k, {:heap, vl, rest, right}}
    end
  end

  #def reduce(nil, acc, _) do init end
  #def reduce({:node, val, left, right}, acc, op) do
  #end

end
