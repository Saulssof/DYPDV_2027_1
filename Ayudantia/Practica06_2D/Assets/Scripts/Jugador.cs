using UnityEngine;

public class Jugador : Personaje
{
    public bool enSuelo = false;

    protected override void Awake()
    {
        base.Awake();
        // Inicialización adicional del jugador
    }

    private void OnCollisionEnter2D(Collision2D col)
    {
        Debug.Log("Colisionando con: " + col.gameObject.name);

        if (col.gameObject.CompareTag("Suelo"))
        {
            enSuelo = true;
        }
    }

    private void OnCollisionStay2D(Collision2D col)
    {
        Debug.Log("Aun colisionando con: " + col.gameObject.name);

        if (col.gameObject.CompareTag("Suelo"))
        {
            enSuelo = true;
        }
    }

    private void OnCollisionExit2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Suelo"))
        {
            enSuelo = false;
        }
    }
}