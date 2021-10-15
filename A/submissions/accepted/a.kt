class NOC(record: String): Comparable<NOC> {
    val g: Int
    val s: Int
    val b: Int
    val name: String
    init {
        val tokens = record.split(" ")
        g = tokens[0].toInt()
        s = tokens[1].toInt()
        b = tokens[2].toInt()
        name = tokens.subList(3, tokens.size).joinToString(" ")
    }
    override operator fun compareTo(o: NOC): Int {
        return (1004004*(o.g-g) + 1002*(o.s-s) + (o.b-b)).compareTo(0)
    }
}

fun main() {
    val n = readLine()!!.toInt()
    val nocs = (1..n).map{ NOC(readLine()!!) }
    println(nocs.minOrNull()!!.name)
}
