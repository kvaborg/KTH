defmodule Philosopher do

  def sleep(0) do :ok end
  def sleep(t) do 
    :timer.sleep(:rand.uniform(t))
  end

  def start(hunger, right, left, name, ctrl) do 
    philosopher = spawn_link(fn() -> 
      dream(hunger, left, right, name, ctrl) end) 
  end
  
  def dream(hunger, left, right, name, ctrl) do
    sleep(50)
    IO.puts("#{name} woke up!")
    wait(hunger, left, right, name, ctrl)
  end

  def wait(hunger, left, right, name, ctrl) do 
    Chopstick.request(left)
    IO.puts("#{name} received left chopstick!")
    Chopstick.request(right)
    IO.puts("#{name} received right chopstick!")
    eat(hunger, left, right, name, ctrl)
  end

  def eat(hunger, left, right, name, ctrl) do 
    sleep(hunger)
    Chopstick.return(left)
    Chopstick.return(right)
    send ctrl, :done
    IO.puts("#{name} has finished eating! ZzzZzzzZz")
    dream(hunger, left, right, name, ctrl)
  end

  def sleep(0) do :ok end
  def sleep(t) do
    :timer.sleep(:rand.uniform(t))
  end
end
