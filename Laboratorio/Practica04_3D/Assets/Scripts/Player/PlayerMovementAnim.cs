using UnityEngine;

public class PlayerMovementAnim : MonoBehaviour
{
    Animator anim;
    CharacterController controller;

    void Start()
    {
        anim = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();
    }

    void Update()
    {
        float x = Input.GetAxis("Horizontal");
        float z = Input.GetAxis("Vertical");

        float speedValue = new Vector2(x, z).magnitude;

        if (Input.GetKey(KeyCode.LeftShift))
        {
            speedValue = 1f;
        }
        else if (speedValue > 0)
        {
            speedValue = 0.5f;
        }
        else
        {
            speedValue = 0f;
        }

        anim.SetFloat("Speed", speedValue);

        if (Input.GetKeyDown(KeyCode.Space))
        {
            anim.SetBool("IsJumping", true);
        }
        else
        {
            anim.SetBool("IsJumping", false);
        }
    }
}