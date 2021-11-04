class Account
    attr_reader :balance
    def initialize()
        @balance = 0
    end

    def deposit(yen)
        @balance += yen
    end

    def withdraw(yen)
        if yen > @balance then
            puts "ERROR: 残高が足りません"
            return -1
        end

        @balance -= yen
        return yen
    end

    def transfer(dest_account, yen)
        r = self.withdraw(yen)
        if r < 0 then
            return
        end
        dest_account.deposit(yen)
    end
end

a = Account.new #aの口座
a.deposit(3000) #aの口座に3000円預ける
b = Account.new #bの口座
b.deposit(1000) #bの口座に1000円預ける (a: 3000, b: 1000)
b.withdraw(500) #bの口座から500円引き出す (a: 3000, b: 500)
a.transfer(b, 2000) #aの口座からbの口座に2000円振り込む (a: 1000, b: 2500)
puts a.balance #aの口座残高を表示
puts b.balance #bの口座残高を表示
b.transfer(a, 5000) #bの口座からaの口座に5000円振り込む
